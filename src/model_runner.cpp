#include "model_runner.h"
#include <algorithm>
#include <iostream>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/interpreter_builder.h"

ModelRunner::ModelRunner(const std::string &model_path)
    : model_path_(model_path) {}

bool ModelRunner::loadModel() {
    std::cout << "Loading model from: " << model_path_ << "\n";
    model_ = tflite::FlatBufferModel::BuildFromFile(model_path_.c_str());
    if (!model_) {
        std::cerr << "Failed to load TFLite model.\n";
        return false;
    }

    tflite::ops::builtin::BuiltinOpResolver resolver;
    tflite::InterpreterBuilder builder(*model_, resolver);
    if (builder(&interpreter_) != kTfLiteOk || !interpreter_) {
        std::cerr << "Failed to create TFLite interpreter.\n";
        return false;
    }

    if (interpreter_->AllocateTensors() != kTfLiteOk) {
        std::cerr << "Failed to allocate TFLite tensors.\n";
        return false;
    }

    std::cout << "Model loaded and tensors allocated successfully.\n";
    return true;
}

bool ModelRunner::setInputData(const std::vector<float> &input_data) {
    if (!interpreter_) {
        std::cerr << "Interpreter not initialized.\n";
        return false;
    }

    const auto inputs = interpreter_->inputs();
    if (inputs.empty()) {
        std::cerr << "No input tensors found.\n";
        return false;
    }

    const int input_index = inputs[0];
    TfLiteTensor *input_tensor = interpreter_->tensor(input_index);
    if (!input_tensor || input_tensor->type != kTfLiteFloat32) {
        std::cerr << "Unsupported input tensor type. Only float32 is supported.\n";
        return false;
    }

    size_t expected_values = input_tensor->bytes / sizeof(float);
    if (input_data.size() != expected_values) {
        std::cerr << "Input data size mismatch: expected " << expected_values
                  << " values but got " << input_data.size() << ".\n";
        return false;
    }

    float *input_buffer = interpreter_->typed_tensor<float>(input_index);
    if (!input_buffer) {
        std::cerr << "Failed to access input tensor buffer.\n";
        return false;
    }

    std::copy(input_data.begin(), input_data.end(), input_buffer);
    return true;
}

bool ModelRunner::runInference() {
    if (!interpreter_) {
        std::cerr << "Interpreter not initialized.\n";
        return false;
    }

    if (interpreter_->Invoke() != kTfLiteOk) {
        std::cerr << "TFLite inference failed.\n";
        return false;
    }

    return true;
}

std::vector<float> ModelRunner::getOutput() const {
    std::vector<float> output;
    if (!interpreter_) {
        return output;
    }

    const auto outputs = interpreter_->outputs();
    if (outputs.empty()) {
        return output;
    }

    const int output_index = outputs[0];
    const TfLiteTensor *output_tensor = interpreter_->tensor(output_index);
    if (!output_tensor) {
        return output;
    }

    if (output_tensor->type != kTfLiteFloat32) {
        std::cerr << "Unsupported output tensor type. Only float32 is supported.\n";
        return output;
    }

    const float *output_buffer = interpreter_->typed_tensor<float>(output_index);
    if (!output_buffer) {
        return output;
    }

    size_t output_values = output_tensor->bytes / sizeof(float);
    output.assign(output_buffer, output_buffer + output_values);
    return output;
}

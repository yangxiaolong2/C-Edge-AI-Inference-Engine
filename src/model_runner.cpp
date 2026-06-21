#include "model_runner.h"
#include <iostream>

ModelRunner::ModelRunner(const std::string &model_path)
    : model_path_(model_path) {}

bool ModelRunner::loadModel() {
    std::cout << "Loading model from: " << model_path_ << "\n";
    // TODO: Load TFLite model into interpreter.
    return true;
}

bool ModelRunner::runInference() {
    std::cout << "Running inference...\n";
    // TODO: Run inference on preprocessed input data.
    return true;
}

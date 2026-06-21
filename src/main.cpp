#include "model_runner.h"
#include "image_preprocessor.h"
#include "benchmark.h"
#include <iostream>

int main() {
    std::cout << "C-Edge AI Inference Engine starting...\n";

    ImagePreprocessor preprocessor("data/sample_images/sample.jpg");
    std::vector<float> input_data = preprocessor.preprocess();

    ModelRunner runner("models/model_fp32.tflite");
    if (!runner.loadModel()) {
        return 1;
    }

    if (!runner.setInputData(input_data)) {
        return 1;
    }

    if (!runner.runInference()) {
        return 1;
    }

    std::vector<float> output = runner.getOutput();
    std::cout << "Inference completed. Output size: " << output.size() << "\n";
    if (!output.empty()) {
        std::cout << "First output value: " << output[0] << "\n";
    }

    Benchmark bench;
    bench.run();

    return 0;
}

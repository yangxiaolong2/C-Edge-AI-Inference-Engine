#include "image_preprocessor.h"
#include <iostream>

ImagePreprocessor::ImagePreprocessor(const std::string &image_path)
    : image_path_(image_path) {}

std::vector<float> ImagePreprocessor::preprocess() {
    std::cout << "Preprocessing image: " << image_path_ << "\n";
    // TODO: Replace with real image loading, resizing, and normalization.
    const int width = 224;
    const int height = 224;
    const int channels = 3;
    return std::vector<float>(width * height * channels, 0.0f);
}

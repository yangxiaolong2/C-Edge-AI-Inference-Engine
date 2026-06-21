#include "image_preprocessor.h"
#include <iostream>

ImagePreprocessor::ImagePreprocessor(const std::string &image_path)
    : image_path_(image_path) {}

bool ImagePreprocessor::preprocess() {
    std::cout << "Preprocessing image: " << image_path_ << "\n";
    // TODO: Load and preprocess image for model inference.
    return true;
}

#ifndef IMAGE_PREPROCESSOR_H
#define IMAGE_PREPROCESSOR_H

#include <string>
#include <vector>

class ImagePreprocessor {
public:
    explicit ImagePreprocessor(const std::string &image_path);
    std::vector<float> preprocess();

private:
    std::string image_path_;
};

#endif // IMAGE_PREPROCESSOR_H

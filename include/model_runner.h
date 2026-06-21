#ifndef MODEL_RUNNER_H
#define MODEL_RUNNER_H

#include <memory>
#include <string>
#include <vector>

namespace tflite {
class Interpreter;
class FlatBufferModel;
}

class ModelRunner {
public:
    explicit ModelRunner(const std::string &model_path);
    bool loadModel();
    bool setInputData(const std::vector<float> &input_data);
    bool runInference();
    std::vector<float> getOutput() const;

private:
    std::string model_path_;
    std::unique_ptr<tflite::FlatBufferModel> model_;
    std::unique_ptr<tflite::Interpreter> interpreter_;
};

#endif // MODEL_RUNNER_H

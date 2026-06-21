#ifndef MODEL_RUNNER_H
#define MODEL_RUNNER_H

#include <string>

class ModelRunner {
public:
    explicit ModelRunner(const std::string &model_path);
    bool loadModel();
    bool runInference();

private:
    std::string model_path_;
};

#endif // MODEL_RUNNER_H

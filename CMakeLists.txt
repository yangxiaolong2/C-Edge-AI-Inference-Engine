cmake_minimum_required(VERSION 3.15)
project(C_Edge_AI_Inference_Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(C_Edge_AI_Inference_Engine
    src/main.cpp
    src/model_runner.cpp
    src/image_preprocessor.cpp
    src/benchmark.cpp
    src/utils.cpp
)

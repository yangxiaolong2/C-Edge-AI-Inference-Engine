cmake_minimum_required(VERSION 3.15)
project(C_Edge_AI_Inference_Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_path(TFLITE_INCLUDE_DIR tensorflow/lite/interpreter.h)
find_library(TFLITE_LIBRARY
    NAMES tensorflowlite tensorflow-lite tflite
)

if(NOT TFLITE_INCLUDE_DIR OR NOT TFLITE_LIBRARY)
    message(FATAL_ERROR "TensorFlow Lite headers or library not found. Install TensorFlow Lite C++ library.")
endif()

include_directories(${PROJECT_SOURCE_DIR}/include ${TFLITE_INCLUDE_DIR})

add_executable(C_Edge_AI_Inference_Engine
    src/main.cpp
    src/model_runner.cpp
    src/image_preprocessor.cpp
    src/benchmark.cpp
    src/utils.cpp
)

target_link_libraries(C_Edge_AI_Inference_Engine PRIVATE ${TFLITE_LIBRARY})

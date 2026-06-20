cmake_minimum_required(VERSION 3.13)
project(jsi_example)

add_library(jsi_example SHARED MathOperations.cpp)

target_include_directories(jsi_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(ReactAndroid REQUIRED CONFIG)

target_link_libraries(jsi_example
    ReactAndroid::jsi
    android
    log
)

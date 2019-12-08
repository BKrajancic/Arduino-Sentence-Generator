cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

add_executable(${PROJECT_NAME} demo.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
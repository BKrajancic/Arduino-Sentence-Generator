cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

add_executable(${PROJECT_NAME} demo.cpp)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC lib)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(demo PRIVATE -Wall)
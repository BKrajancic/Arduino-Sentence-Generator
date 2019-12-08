cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

find_package(Boost COMPONENTS unit_test_framework)
add_executable(${PROJECT_NAME}
main.hpp
main_test.cpp)

target_link_libraries(${PROJECT_NAME}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

cmake_minimum_required(VERSION 3.0.0)
project(test CXX)

include_directories (lib PUBLIC ../lib)

find_package(Boost COMPONENTS unit_test_framework)
add_executable(${PROJECT_NAME}
main_test.cpp)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
lib
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
target_compile_options(test PRIVATE -Wall)

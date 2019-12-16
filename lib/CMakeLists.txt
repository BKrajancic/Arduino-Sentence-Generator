
cmake_minimum_required(VERSION 3.0.0)
project(lib CXX)

add_library(${PROJECT_NAME} SHARED
grammar.hpp
monospace_sizer.hpp
sentence_generator.hpp
sizer.hpp
utility_cpp.hpp
macros/macro.hpp
macros/no_space_begin.hpp
macros/no_space_end.hpp
macros/remove_empty.hpp
)

target_include_directories (lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

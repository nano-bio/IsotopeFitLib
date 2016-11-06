cmake_minimum_required(VERSION 2.8.8)
project(IsotopeFitLib)

include_directories(include)

file(GLOB SRC "src/*.cpp")

add_library(ifl STATIC ${SRC})
set_property(TARGET ifl PROPERTY CXX_STANDARD 14)
set_property(TARGET ifl PROPERTY CXX_STANDARD_REQUIRED ON)
set_target_properties(ifl PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
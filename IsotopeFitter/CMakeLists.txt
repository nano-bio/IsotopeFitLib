cmake_minimum_required(VERSION 2.8.8)
project(IsotopeFitter)

#set(PROJECT_LINK_LIBS_IFL libifl.a)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

link_directories(/usr/lib/x86_64-linux-gnu /usr/local/lib ${CMAKE_SOURCE_DIR}/../IsotopeFitLib/lib)

include_directories(include)

file(GLOB SRC "src/*.cpp")

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${Boost_INCLUDE_DIRS}
)

add_executable(isotopefitter ${SRC})
set_property(TARGET isotopefitter PROPERTY CXX_STANDARD 14)
set_property(TARGET isotopefitter PROPERTY CXX_STANDARD_REQUIRED ON)
set_target_properties(isotopefitter PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(isotopefitter PROPERTIES LINK_SEARCH_END_STATIC 1)
set_target_properties(isotopefitter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
target_link_libraries(isotopefitter libc.a libdl.a libifl.a libmatio.a libhdf5.a libhdf5_cpp.a libsz.a libz.a libgsl.a libgslcblas.a ${Boost_LIBRARIES})

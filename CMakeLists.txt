cmake_minimum_required(VERSION 3.0.0)

project(BiPlex LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wno-reorder -O3 -march=native -g -pg -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -pg -O0 -fsanitize=address")

set(EXECUTABLE_OUTPUT_PATH bin)

set(EXECUTABLE_FILENAME run)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/biplex)


add_executable(${EXECUTABLE_FILENAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${EXECUTABLE_FILENAME} BiPlex BiGraph)

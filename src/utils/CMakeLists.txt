cmake_minimum_required(VERSION 3.0.0)

add_library(FastIO INTERFACE)
target_include_directories(FastIO INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(BiGraph INTERFACE)
target_include_directories(BiGraph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Graph INTERFACE)
target_include_directories(Graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Hash INTERFACE)
target_include_directories(Hash INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(LinearHeap INTERFACE)
target_include_directories(LinearHeap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(VertexSet INTERFACE)
target_include_directories(VertexSet INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

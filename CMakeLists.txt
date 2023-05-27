cmake_minimum_required(VERSION 3.23)
project(sat4gpu LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

add_library(sat4gpu STATIC
        include/backend.hpp
        include/clause.hpp
        include/lit.hpp
        include/solution.hpp
        include/solver.hpp
        include/var.hpp
        src/cuda_backend.cu
        src/cuda_backend.cuh
        src/solver.cpp)

target_include_directories(sat4gpu PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_options(sat4gpu PRIVATE "--extended-lambda")
target_compile_options(sat4gpu PRIVATE "--expt-extended-lambda")
set_target_properties(sat4gpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

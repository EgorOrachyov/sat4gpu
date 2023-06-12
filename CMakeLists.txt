cmake_minimum_required(VERSION 3.23)
project(sat4gpu LANGUAGES CXX CUDA)

######################################################################
## public options

option(SAT4GPU_BUILD_APP "Build library example application" YES)
option(SAT4GPU_BUILD_TESTS "Build library unit tests" YES)

######################################################################
## Internal definitions

set(SAT4GPU_DEFINES)
set(SAT4GPU_DEBUG NO)
set(SAT4GPU_RELEASE NO)
set(SAT4GPU_TARGET_LINUX NO)
set(SAT4GPU_TARGET_WINDOWS NO)
set(SAT4GPU_TARGET_MACOSX NO)
set(SAT4GPU_ARCH)

####################################################################
## Define platform
##  - WINDOWS = Windows Desktop
##  - MACOSX  = MacOS X
##  - LINUX   = Linux

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SAT4GPU_TARGET_WINDOWS YES)
    set(SAT4GPU_ARCH "win_x64")
    list(APPEND SAT4GPU_DEFINES SAT4GPU_TARGET_WINDOWS)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(SAT4GPU_TARGET_LINUX YES)
    set(SAT4GPU_ARCH "linux_x64")
    list(APPEND SAT4GPU_DEFINES SAT4GPU_TARGET_LINUX)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(SAT4GPU_TARGET_MACOSX YES)
    if (NOT SAT4GPU_ARCH)
        if (NOT CMAKE_OSX_ARCHITECTURES)
            if ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "arm64")
                set(SAT4GPU_ARCH "macos_arm64")
            else ()
                set(SAT4GPU_ARCH "macos_x64")
            endif ()
        else ()
            if ("${CMAKE_OSX_ARCHITECTURES}" STREQUAL "arm64")
                set(SAT4GPU_ARCH "macos_arm64")
            else ()
                set(SAT4GPU_ARCH "macos_x64")
            endif ()
        endif ()
    endif ()
    message(STATUS "Build macos binaries for ${SAT4GPU_ARCH} architecture")
    list(APPEND SAT4GPU_DEFINES SAT4GPU_TARGET_MACOSX)
else ()
    message(FATAL_ERROR "Unsupported target platform")
endif ()

####################################################################
## Define Build type

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(SAT4GPU_DEBUG YES)
    list(APPEND SAT4GPU_DEFINES SAT4GPU_DEBUG)
    message(STATUS "Build SAT4GPU in debug mode (specified)")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set(SAT4GPU_RELEASE YES)
    list(APPEND SAT4GPU_DEFINES SAT4GPU_RELEASE)
    message(STATUS "Build SAT4GPU in release mode (specified)")
elseif (CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set(SAT4GPU_RELEASE YES)
    list(APPEND SAT4GPU_DEFINES SAT4GPU_DEBUG_RELEASE)
    message(STATUS "Build SAT4GPU in release mode with debug info (specified)")
else ()
    set(SAT4GPU_RELEASE YES)
    set(CMAKE_BUILD_TYPE Release)
    list(APPEND SAT4GPU_DEFINES SAT4GPU_RELEASE)
    message(STATUS "Build SAT4GPU in release mode (default, not specified)")
endif ()

##################################################################
## Compiler and language specifics

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CUDA_STANDARD 17)

if (SAT4GPU_TARGET_WINDOWS)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        list(APPEND SAT4GPU_DEFINES SAT4GPU_MSVC)
    else ()
        message(FATAL_ERROR "Supported only MSVC compiler for Windows platform")
    endif ()
endif ()

##################################################################
## Target options and defs functions
## (use this functions to configure build targets)

function(sat4gpu_target_compile_definitions target)
    foreach (DEFINITION ${SAT4GPU_DEFINES})
        target_compile_definitions(${target} PUBLIC ${DEFINITION})
    endforeach ()

    if (SAT4GPU_TARGET_WINDOWS)
        target_compile_definitions(${target}
                PUBLIC WIN32
                PUBLIC _WIN32
                PUBLIC _WINDOWS
                PUBLIC UNICODE
                PUBLIC _UNICODE
                PUBLIC _CRT_SECURE_NO_WARNINGS
                PUBLIC _SCL_SECURE_NO_WARNINGS)
    endif ()
endfunction()

######################################################################
## Dependencies config

add_subdirectory(deps/robin_hood)
add_subdirectory(deps/svector)

if (SAT4GPU_BUILD_APP)
    message(STATUS "Add cxxopts as arguments parser for example applications")
    set(CXXOPTS_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(CXXOPTS_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(CXXOPTS_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    set(CXXOPTS_ENABLE_WARNINGS OFF CACHE BOOL "" FORCE)
    set(CXXOPTS_USE_UNICODE_HELP OFF CACHE BOOL "" FORCE)
    add_subdirectory(deps/cxxopts)
endif ()

if (SAT4GPU_BUILD_TESTS)
    message(STATUS "Add Google test as unit test framework")
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
    set(gtest_hide_internal_symbols ON CACHE BOOL "" FORCE)
    add_subdirectory(deps/gtest)
endif ()

######################################################################
## Source code configuration

add_library(sat4gpu STATIC
        include/backend.hpp
        include/clause.hpp
        include/lit.hpp
        include/solution.hpp
        include/solver.hpp
        include/var.hpp
        src/cpu_naive_comb_backend.cpp
        src/cpu_naive_comb_backend.hpp
        src/cuda_backend.cu
        src/cuda_backend.cuh
        src/clause.cpp
        src/lit.cpp
        src/solver.cpp)

target_include_directories(sat4gpu PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(sat4gpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

sat4gpu_target_compile_definitions(sat4gpu)
set_target_properties(sat4gpu PROPERTIES OUTPUT_NAME "sat4gpu")

######################################################################
## Additional

if (SAT4GPU_BUILD_APP)
    add_executable(sat app/sat.cpp)
    target_link_libraries(sat PRIVATE sat4gpu)
    target_link_libraries(sat PRIVATE cxxopts)
    set_target_properties(sat PROPERTIES OUTPUT_NAME "sat")
endif ()

if (SAT4GPU_BUILD_TESTS)
    add_subdirectory(test)
endif ()
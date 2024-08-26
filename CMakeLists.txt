# Copyright MediaZ Teknoloji A.S. All Rights Reserved.
cmake_minimum_required(VERSION 3.24.2)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)

if (NOT WITH_NODOS_WORKSPACE)
    message(FATAL_ERROR "This repo currently does not support builds without Nodos workspace. "
    "Place this repo under nodos-workspace/Module folder and run cmake -S ./Toolchain/CMake -B Build from workspace root.")
endif()

nos_find_sdk("1.2.0" NOS_PLUGIN_SDK_TARGET NOS_SUBSYSTEM_SDK_TARGET NOS_SDK_DIR)

add_subdirectory(AdderSubsystem)
add_subdirectory(AdderNodes)
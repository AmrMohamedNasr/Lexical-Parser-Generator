cmake_minimum_required(VERSION 3.8)
project(compilers)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NfaBuilder.cpp NfaBuilder.h NfaCombiner.cpp NfaCombiner.h NfaDfaConverter.cpp NfaDfaConverter.h DfaMinimizer.cpp DfaMinimizer.h)
add_executable(compilers ${SOURCE_FILES})
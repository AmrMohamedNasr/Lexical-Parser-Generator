cmake_minimum_required(VERSION 3.8)
project(compilers)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp builder/NfaBuilder.cpp builder/NfaBuilder.h combiner/NfaCombiner.cpp combiner/NfaCombiner.h converter/NfaDfaConverter.cpp converter/NfaDfaConverter.h minimizer/DfaMinimizer.cpp minimizer/DfaMinimizer.h models/FiniteStateAcceptor.cpp models/FiniteStateAcceptor.h models/Node.cpp models/Node.h models/Edge.cpp models/Edge.h)
add_executable(compilers ${SOURCE_FILES})
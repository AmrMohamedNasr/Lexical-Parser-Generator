cmake_minimum_required(VERSION 3.8)
project(compilers)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp p1_tests.h builder/NfaBuilder.cpp builder/NfaBuilder.h combiner/NfaCombiner.cpp combiner/NfaCombiner.h converter/NfaDfaConverter.cpp converter/NfaDfaConverter.h minimizer/DfaMinimizer.cpp minimizer/DfaMinimizer.h models/Nfa.h models/NfaToken.h models/NfaToken.cpp models/Node.cpp models/Node.h models/Edge.cpp models/Edge.h models/SupportingNfaNodes.cpp models/SupportingNfaNodes.h)

file(GLOB_RECURSE source_list "combiner/*.cpp" "combiner/*.h" "builder/*.cpp" "builder/*.hpp"
        "converter/*.cpp" "converter/*.h" "minimizer/*.cpp" "minimizer/*.h"
        "models/*.cpp" "models/*.h" "grammer_parser/*.h" "grammer_parser/*.cpp")

add_executable(compilers ${SOURCE_FILES} ${source_list})
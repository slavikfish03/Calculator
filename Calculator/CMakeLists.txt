cmake_minimum_required(VERSION 3.26)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_HEADERS Calculator.hpp CoreCalculator.hpp PluginManager.hpp)
add_executable(Calculator ${PROJECT_SOURCE_DIR}/ Main.cpp Calculator.cpp CoreCalculator.cpp PluginManager.cpp)

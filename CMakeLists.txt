cmake_minimum_required(VERSION 2.8)

# About project
project(genesis)
set(VERSION_MINOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Set envs.
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -DNDEBUG -g -O3 -std=c++11 -DGEN_TLOG -DGEN_NANO_SECOND_SLEEP")

# Enable test in project.
enable_testing()

# Add subdiretories.
add_subdirectory(genesis)
add_subdirectory(tools)
add_subdirectory(test)
add_subdirectory(doc)


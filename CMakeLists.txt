# CMake version
cmake_minimum_required (VERSION 3.9)
MESSAGE(STATUS "CMAKE_ROOT: " ${CMAKE_ROOT})

# Project name
project(The-Blow-Eagle-stealer VERSION 1.0.0 LANGUAGES CXX)

# Turn on the verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

# Compiler vendors
## g++
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.3")
    message(FATAL_ERROR "\nCpp-Taskflow requires g++ at least v7.3")
  endif()
## clang++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.0")
    message(FATAL_ERROR "\nCpp-Taskflow requires clang++ at least v6.0")
  endif() 
## AppleClang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0")
    message(FATAL_ERROR "\nCpp-Taskflow requires AppleClang at least v11.0")
  endif()
## microsoft visual c++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(NOT MSVC_VERSION GREATER_EQUAL 1914)
    message(FATAL_ERROR "\nCpp-Taskflow requires MSVC++ at least v14.14") 
  endif()
else()
  message(FATAL_ERROR "\n\
Cpp-Taskflow currently supports the following compilers:\n\
- g++ v7.3 or above\n\
- clang++ v6.0 or above\n\
- MSVC++ v19.14 or above\n\
")
endif()

# defult release build
set(WSQ_DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${WSQ_DEFAULT_BUILD_TYPE}'")
  set(
    CMAKE_BUILD_TYPE "${WSQ_DEFAULT_BUILD_TYPE}" 
    CACHE
    STRING "Choose the type of build." 
    FORCE
  )
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE 
    CMAKE_BUILD_TYPE 
    PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
  )
endif()



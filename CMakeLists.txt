cmake_minimum_required(VERSION 3.5)
project(br_ms5837)

# Default to C++14
if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

find_package(ament_cmake REQUIRED)

# Hack for MRAA
set(mraa_INCLUDE_DIRS "/usr/include")
set(mraa_FOUND true)

# x86 vs ARM -- this works on Linux
if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
  message(STATUS "Detected aarch64")
  set(mraa_LIBRARIES "/usr/lib/aarch64-linux-gnu/libmraa.so")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROCESSOR_AARCH64")
else()
  message(STATUS "Default to x86_64")
  set(mraa_LIBRARIES "/usr/lib/x86_64-linux-gnu/libmraa.so")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROCESSOR_X86_64")
endif()

# Local includes
include_directories(
  include
)

#=============
# Library
#=============

add_library(
  ms5837 SHARED
  MS5837.cpp
)
ament_export_libraries(ms5837)

#=============
# Example
#=============

add_executable(
  example
  example.cpp
  MS5837.cpp
)
ament_target_dependencies(
  example
  mraa
)

#=============
# Install
#=============

# Export include directory
ament_export_include_directories(include)

# Install include directory
install(DIRECTORY include/${PROJECT_NAME} DESTINATION include)

## Install library
install(
  TARGETS ms5837
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install executable
install(
  TARGETS example
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
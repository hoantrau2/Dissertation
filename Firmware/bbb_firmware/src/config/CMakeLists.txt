# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of module
set(MODULE_NAME bbb_config)

# List all sources
list(APPEND BBB_CONFIG
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config.cpp
)

# Add libraries
add_library(${MODULE_NAME} STATIC ${BBB_CONFIG})

# Include directories
target_include_directories(${MODULE_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

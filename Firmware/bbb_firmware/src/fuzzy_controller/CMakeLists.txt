# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of module
set(MODULE_NAME bbb_fuzzy_controller)

# List all sources
list(APPEND BBB_FUZZY_CONTROLLER
  ${CMAKE_CURRENT_SOURCE_DIR}/src/fuzzy_controller.cpp
)

# Add libraries
add_library(${MODULE_NAME} STATIC ${BBB_FUZZY_CONTROLLER})

# Include directories
target_include_directories(${MODULE_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/config/include
  ${CMAKE_SOURCE_DIR}/src/fuzzy_controller/include
)

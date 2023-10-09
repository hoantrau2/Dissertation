# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of module
set(MODULE_NAME bbb_state_machine)

# List all sources
list(APPEND IO__SCHEDULER__H 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/state_machine.cpp)


# Add libraries
add_library(${MODULE_NAME} STATIC ${BBB_IO_STATE_MACHINE})

# Include directories
target_include_directories(${MODULE_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/config/include
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${MODULE_NAME} 
  pico_stdlib
)

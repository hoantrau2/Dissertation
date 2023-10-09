# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Set name of module
set(MODULE_NAME bbb_ros_comm)

# List all sources
list(APPEND BBB_ROS_COMM 
# This path should be fixed in the project
  ${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk/pico_uart_transport.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ros_comm.cpp
)

# Add libraries
add_library(${MODULE_NAME} STATIC ${BBB_ROS_COMM})

# Include directories
target_include_directories(${MODULE_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk
  ${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk/libmicroros/include
)

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${MODULE_NAME} 
  pico_stdlib
  microros
)

# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(bbbfw C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# ROS library
link_directories(${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk/libmicroros)

# Add modules
add_subdirectory(${CMAKE_SOURCE_DIR}/src/battery)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/buzzer)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/config)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/display)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/led)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/ros_comm)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/scheduler)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/state_machine)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/speed_controller)

list(APPEND BBB_MODULE_LIST 
bbb_battery
bbb_buzzer
bbb_config
bbb_display
bbb_led
bbb_ros_comm
microros
bbb_scheduler
bbb_state_machine
bbb_speed_controller
)

list(APPEND BBB_MODULE_HEADER_LIST 
  ${CMAKE_SOURCE_DIR}/src/battery/include
  ${CMAKE_SOURCE_DIR}/src/buzzer/include
  ${CMAKE_SOURCE_DIR}/src/config/include
  ${CMAKE_SOURCE_DIR}/src/display/include
  ${CMAKE_SOURCE_DIR}/src/led/include
  ${CMAKE_SOURCE_DIR}/src/ros_comm/include
  ${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk
  ${CMAKE_SOURCE_DIR}/pico/micro_ros_raspberrypi_pico_sdk/libmicroros/include
  ${CMAKE_SOURCE_DIR}/src/scheduler/include
  ${CMAKE_SOURCE_DIR}/src/state_machine/include
  ${CMAKE_SOURCE_DIR}/src/speed_controller/include
)

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
  main.cpp
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
  pico_stdlib
  pico_multicore
  
  ${BBB_MODULE_LIST}
)

# Include header directories
target_include_directories(${PROJECT_NAME} PRIVATE
  ${BBB_MODULE_HEADER_LIST}
)

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Generate UF2
pico_add_extra_outputs(bbbfw)
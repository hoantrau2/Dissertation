# Install script for directory: /home/nvhmh/pico_ws/pico/pico-examples/i2c

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/bmp280_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/bus_scan/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/lcd_1602_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/lis3dh_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/mcp9808_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/mma8451_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/mpl3115a2_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/mpu6050_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/ssd1306_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/pa1010d_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/pcf8523_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/ht16k33_i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/i2c/slave_mem_i2c/cmake_install.cmake")

endif()


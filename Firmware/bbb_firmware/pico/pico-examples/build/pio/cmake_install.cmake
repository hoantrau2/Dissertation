# Install script for directory: /home/nvhmh/pico_ws/pico/pico-examples/pio

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
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/addition/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/apa102/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/clocked_input/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/differential_manchester/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/hello_pio/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/hub75/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/i2c/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/ir_nec/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/logic_analyser/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/manchester_encoding/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/onewire/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/pio_blink/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/pwm/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/quadrature_encoder/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/spi/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/squarewave/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/st7789_lcd/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/uart_rx/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/uart_tx/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/pio/ws2812/cmake_install.cmake")

endif()


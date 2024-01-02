# Install script for directory: /home/nvhmh/pico_ws/pico/pico-sdk/lib/tinyusb/examples/device

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
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/pico-sdk/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/audio_4_channel_mic/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/audio_test/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/board_test/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/cdc_dual_ports/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/cdc_msc/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/dfu/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/dfu_runtime/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/dynamic_configuration/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/hid_composite/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/hid_generic_inout/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/hid_multiple_interface/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/midi_test/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/msc_dual_lun/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/net_lwip_webserver/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/uac2_headset/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/usbtmc/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/video_capture/cmake_install.cmake")
  include("/home/nvhmh/pico_ws/pico/pico-examples/build/usb/device/tinyusb_device_examples/webusb_serial/cmake_install.cmake")

endif()


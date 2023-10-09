# bbb_firmware
The firmware of bbb
---
# Preprequisites
- Vscode
- Raspberry Pico [W]
## Install clang-format
```bash
sudo apt install clang-format
```


# Installation
- Download source code
```
cd <workspace>
git clone git@github.com:minht57lab/bbb_firmware.git
cd bbb_firmware
```

- Get SDK and examples
```bash
mkdir pico && cd pico
git clone https://github.com/raspberrypi/pico-sdk.git --branch master
cd pico-sdk
git submodule update --init
cd ..
git clone https://github.com/raspberrypi/pico-examples.git --branch master
git clone https://github.com/micro-ROS/micro_ros_raspberrypi_pico_sdk.git --branch humble
```

- Edit the uROS library in order to be suitable for the C++ project
  - Open `pico_uart_transports.h` in `pico/the micro_ros_raspberrypi_pico_sdk`
  - Add `extern "C"` in each prototype functions
    ```C
    extern "C" bool pico_serial_transport_open(struct uxrCustomTransport * transport);
    extern "C" bool pico_serial_transport_close(struct uxrCustomTransport * transport);
    extern "C" size_t pico_serial_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
    extern "C" size_t pico_serial_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);
    ```

- Install the toolchain
```bash
sudo apt update
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential libstdc++-arm-none-eabi-newlib
```

- Install VSCode
```bash
sudo apt install code
code --install-extension marus25.cortex-debug
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools
```

- Start VSCode
```bash
export PICO_SDK_PATH=<workspace>/pico/pico-sdk
code
```


stm32f4-thrift
==============

An example that uses thrift-nano to read/write messages over usb on an STM32F4.  

Based on USB CDC code I found here: http://vedder.se/2012/07/usb-serial-on-stm32f4/

Building
========

This project uses the [stm32-cmake toolchain](https://github.com/ObKo/stm32-cmake.git) to build.  

1. Clone the toolchain repo
> git clone https://github.com/ObKo/stm32-cmake.git
2. Follow the toolchain repo instructions carefully for building and installing for your board
3. Follow the toolchain repo usage instructions to build one of the provided example projects (like stm32-blinky)

The same instructions used to build the example project may be used to build this project.


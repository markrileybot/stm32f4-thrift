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


Installing
==========

You may use your favorite tool to flash.  I like to use [stlink by texane](https://github.com/texane/stlink) which you may get from the [pacman repo](https://www.archlinux.org/packages/community/x86_64/stlink/) if you're running arch linux.  If you have st-link, just do:

> st-flash --reset write stm32-thrift.bin 0x8000000

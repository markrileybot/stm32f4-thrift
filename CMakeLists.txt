SET(STM32_CHIP $ENV{STM32_CHIP})
SET(STM32_FLASH_SIZE $ENV{STM32_FLASH_SIZE})
SET(STM32_RAM_SIZE $ENV{STM32_RAM_SIZE})
SET(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
SET(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH}) 
SET(TOOLCHAIN_PREFIX $ENV{TOOLCHAIN_PREFIX})
SET(CMAKE_INSTALL_PREFIX $ENV{CMAKE_INSTALL_PREFIX})
SET(STM32_MIN_HEAP_SIZE 4K)

INCLUDE(ExternalProject)
EXTERNALPROJECT_ADD(
	thrift-nano
	PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/lib/thrift-nano-git
	GIT_REPOSITORY https://github.com/markrileybot/thrift-nano.git
	INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/thrift-nano-git
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ""
	TEST_BEFORE_INSTALL 0
)
EXTERNALPROJECT_GET_PROPERTY(thrift-nano PREFIX)
SET(THRIFT_NANO ${PREFIX}/src/thrift-nano/lib/c_nano/src)

PROJECT(stm32-thrift)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
ENABLE_LANGUAGE(ASM)

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	${CMAKE_CURRENT_SOURCE_DIR}/lib/cmsis
	${CMAKE_CURRENT_SOURCE_DIR}/lib/stdperiph
	${CMAKE_CURRENT_SOURCE_DIR}/lib/usbd
	${CMAKE_CURRENT_SOURCE_DIR}/lib/thrift-nano
	${THRIFT_NANO}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/gen-c_nano
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

FILE(GLOB STARTUP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.s)
FILE(GLOB CMSIS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmsis/*.c)
FILE(GLOB CMSIS_HDR ${CMAKE_CURRENT_SOURCE_DIR}/lib/cmsis/*.h)
FILE(GLOB STDPERIPH_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/stdperiph/*.c)
FILE(GLOB STDPERIPH_HDR ${CMAKE_CURRENT_SOURCE_DIR}/lib/stdperiph/*.h)
FILE(GLOB USB_CDC_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/usbd/*.c)
FILE(GLOB USB_CDC_HDR ${CMAKE_CURRENT_SOURCE_DIR}/lib/usbd/*.h)
FILE(GLOB THRIFT_NANO_SRC ${THRIFT_NANO}/thrift-nano/*.c)
FILE(GLOB THRIFT_NANO_HDR ${THRIFT_NANO}/thrift-nano/*.h)
FILE(GLOB GEN_NANO_SRC ${CMAKE_CURRENT_SOURCE_DIR}/lib/gen-c_nano/*.c)
FILE(GLOB GEN_NANO_HDR ${CMAKE_CURRENT_SOURCE_DIR}/lib/gen-c_nano/*.h)
FILE(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
FILE(GLOB HDR ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

SET(PROJECT_SOURCES
	${SRC}
	${CMSIS_SRC}
	${STDPERIPH_SRC}
	${USB_CDC_SRC}
	${THRIFT_NANO_SRC}
	${GEN_NANO_SRC}
	${STARTUP_SRC}
)

SET(STM32_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/stm32_flash.ld)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})
ADD_DEPENDENCIES(${CMAKE_PROJECT_NAME} thrift-nano)

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})
STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})

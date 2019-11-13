# STM32F4-Cube-Firmware
A clone of the STM32F4 Firmware, version 1.21.0. Used in the automated testing of STM32 projects.

## Example use

See [here](https://github.com/alxhoff/STM32-Mechanical-Keyboard) for complete example.

``` cmake 
PROJECT(esp32_keyboard)

set(CMAKE_BUILD_TYPE Debug)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
ENABLE_LANGUAGE(ASM)

# Remove -rdynamic option from linking that is not supported by arm-none-eabi
# Also remove "undefined reference to `_sbrk'" error
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-specs=nano.specs -specs=nosys.specs")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(STM32_CHIP STM32F429ZIT)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

FIND_PACKAGE(Git REQUIRED)
set(CUBE_SOURCE "${CMAKE_BINARY_DIR}/STM32F4-Cube-Firmware")
if(EXISTS ${CUBE_SOURSE})
    message("Cube FW directory exists")
else()
    message("Getting Cube Firmware")
    set(GIT_REPOSITORY "https://github.com/alxhoff/STM32F4-Cube-Firmware.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} clone ${GIT_REPOSITORY} )
endif()

set(STM32Cube_DIR ${CUBE_SOURCE})

FIND_PACKAGE(CMSIS REQUIRED)
FIND_PACKAGE(STM32HAL COMPONENTS adc cortex dma eth flash flash_ramfunc gpio i2c pcd rcc tim uart REQUIRED)
FIND_PACKAGE(STM32LL COMPONENTS usb REQUIRED)
FIND_PACKAGE(USBDevice COMPONENTS HID REQUIRED)

SET(FREERTOS_HEAP_IMPL 4)
FIND_PACKAGE(FreeRTOS)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${PROJECT_SOURCE_DIR}/Inc"
    ${USBDevice_INCLUDE_DIR}
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR}
    ${STM32LL_INCLUDE_DIR}
    ${FreeRTOS_INCLUDE_DIRS}
    )

file(GLOB PROJECT_SOURCES "Src/*.c")

SET(STM32_LINKER_SCRIPT ${CMSIS_LINKER_SCRIPT})

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES} ${STM32HAL_SOURCES} ${STM32LL_SOURCES} ${FreeRTOS_SOURCES} ${USBDevice_SOURCES} ${CMSIS_SOURCES})

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})
STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})
STM32_PRINT_SIZE_OF_TARGETS(${CMAKE_PROJECT_NAME})

```

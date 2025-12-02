cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT ON)

include(external/pico_sdk_import.cmake)

set(PROJECT_TARGET MusicBox)
project(${PROJECT_TARGET} C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)

set(ENABLE_USB_OUTPUT 1)
set(ENABLE_UART_OUTPUT 0)

pico_sdk_init()

add_executable(${PROJECT_TARGET}
    sources/main.cpp
    sources/music_box.cpp

    sources/motor/motor_manager.cpp
    sources/motor/request.cpp
    sources/motor/utilities.cpp
)

target_include_directories(${PROJECT_TARGET} PRIVATE 
    sources
)

target_link_libraries(${PROJECT_TARGET} 
    pico_stdlib  
    hardware_i2c
)

pico_enable_stdio_usb(${PROJECT_TARGET} ${ENABLE_USB_OUTPUT})
pico_enable_stdio_uart(${PROJECT_TARGET} ${ENABLE_UART_OUTPUT})

pico_add_extra_outputs(${PROJECT_TARGET})

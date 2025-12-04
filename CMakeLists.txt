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

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp
)

add_executable(${PROJECT_TARGET} ${PROJECT_SOURCES})

target_compile_definitions(${PROJECT_TARGET} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(${PROJECT_TARGET} PRIVATE 
    sources
)

target_link_libraries(${PROJECT_TARGET} 
    pico_stdlib  
    hardware_i2c
    hardware_adc
)

pico_enable_stdio_usb(${PROJECT_TARGET} ${ENABLE_USB_OUTPUT})
pico_enable_stdio_uart(${PROJECT_TARGET} ${ENABLE_UART_OUTPUT})

pico_add_extra_outputs(${PROJECT_TARGET})

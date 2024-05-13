cmake_minimum_required(VERSION 3.12)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(HelloWorld C CXX ASM) 
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


# rest of your project
add_executable(HelloWorld    HelloWorld.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(HelloWorld pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(HelloWorld 1)
pico_enable_stdio_uart(HelloWorld 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(HelloWorld
)

cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME epd-demo)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")
include("cmake/binutils.cmake")
include("cmake/gdb-helper.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(Middlewares/ST/rfal)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/demo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/logger.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Browser/Browser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/GUI_Paint.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/SPI_RAM.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/ST25R3911/st25r3911.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/ST25R3911/st25r3911_com.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/ST25R3911/st25r3911_interrupt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/ST25R3911/timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Config/DEV_Config.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Fonts/Fonts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Key/Key.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SDcard/SD_Card_APP.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SDcard/SD_Card_Drive.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SDcard/SD_Card_Interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SSD1306/SSD1306.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Browser
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Bsp
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/ST25R3911
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Config
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Fonts
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Key
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SDcard
    ${CMAKE_CURRENT_SOURCE_DIR}/User/SSD1306
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    rfal_driver
)

generate_extra_output(${CMAKE_PROJECT_NAME})
generate_debugger_config(${CMAKE_PROJECT_NAME})

if (WIN32)
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND powershell -Command "Get-Date; Write-Output 'Build completed'")
else ()
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND bash -c "date +'%x %T' && echo 'Build completed'")
endif ()
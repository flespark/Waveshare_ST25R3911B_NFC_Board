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

# Log interface selection
set(LOG_INTERFACE_LIST none uart uart_dma rtt)
set(LOG_INTERFACE uart CACHE STRING "Default log interface is uart")
set_property(CACHE LOG_INTERFACE PROPERTY STRINGS ${LOG_INTERFACE_LIST})
set_property(CACHE LOG_INTERFACE PROPERTY ADVANCED)

if(${LOG_INTERFACE} STREQUAL none)
    message(STATUS "Log not enabled")
elseif(${LOG_INTERFACE} STREQUAL uart)
    message(STATUS "Log interface use UART")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        LOG_USING_UART
    )
elseif(${LOG_INTERFACE} STREQUAL rtt)
    message(STATUS "Log interface use RTT, NOTICE: RTT will wake MCU from low power")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        LOG_USING_RTT
    )

    add_subdirectory(Middlewares/Third_Party/SEGGER_RTT)
    target_link_libraries(${CMAKE_PROJECT_NAME} SEGGER_RTT)

else()
    message(FATAL_ERROR "Unsupported log interface selected...")
endif()

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)
add_subdirectory(Middlewares/ST/RFAL)
add_subdirectory(Middlewares/ST/st25r_common)
# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_CURRENT_SOURCE_DIR}/Src/demo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/Browser/Browser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/GUI_Paint.c
    ${CMAKE_CURRENT_SOURCE_DIR}/User/BSP/SPI_RAM.c
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
    RFAL
    st25r_common
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
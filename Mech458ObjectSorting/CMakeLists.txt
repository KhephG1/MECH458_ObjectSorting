cmake_minimum_required(VERSION 3.13)

# ---------------------------------------------------------------------------
# Toolchain (must be set before project())
# ---------------------------------------------------------------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

# Skip the host link test; AVR has no OS to link a test program against
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(firmware C ASM)

# ---------------------------------------------------------------------------
# User settings (override with -DNAME=value on the cmake command line)
# ---------------------------------------------------------------------------
set(MCU       "atmega2560" CACHE STRING "Target microcontroller")
set(F_CPU     "16000000UL" CACHE STRING "CPU clock in Hz")
set(SRC_DIR   "${CMAKE_SOURCE_DIR}" CACHE PATH "Folder containing the .c/.h files")

# avrdude settings (Arduino Mega 2560 bootloader defaults)
set(AVRDUDE_PROGRAMMER "wiring"       CACHE STRING "avrdude programmer id")
set(AVRDUDE_PORT       "/dev/ttyACM0" CACHE STRING "Serial port, e.g. COM3 on Windows")
set(AVRDUDE_BAUD       "115200"       CACHE STRING "Programmer baud rate")

# ---------------------------------------------------------------------------
# Sources: every .c file in SRC_DIR is compiled into one executable
# ---------------------------------------------------------------------------
file(GLOB SOURCES CONFIGURE_DEPENDS "${SRC_DIR}/*.c")

if(NOT SOURCES)
    message(FATAL_ERROR "No .c files found in ${SRC_DIR}")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")

# Lets the .c files find the .h files in the same folder
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

target_compile_definitions(${PROJECT_NAME} PRIVATE F_CPU=${F_CPU})

target_compile_options(${PROJECT_NAME} PRIVATE
    -mmcu=${MCU}
    -std=gnu99
    -Os
    -Wall
    -Wextra
    -ffunction-sections
    -fdata-sections
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mmcu=${MCU}
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
)

# ---------------------------------------------------------------------------
# Post-build: produce .hex and print memory usage
# ---------------------------------------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
            $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} --mcu=${MCU} --format=avr
            $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Generating ${PROJECT_NAME}.hex"
)

# ---------------------------------------------------------------------------
# Optional: `cmake --build build --target flash`
# ---------------------------------------------------------------------------
add_custom_target(flash
    COMMAND avrdude -p ${MCU} -c ${AVRDUDE_PROGRAMMER} -P ${AVRDUDE_PORT}
            -b ${AVRDUDE_BAUD} -D -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}
    COMMENT "Flashing ${PROJECT_NAME}.hex to ${MCU}"
)

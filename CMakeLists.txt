cmake_minimum_required(VERSION 3.13)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/pico/pico-sdk")
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picow_ble_hid_keyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picow_ble_hid_keyboard 
      picow_ble_hid_keyboard.c 
      tusb_hid.c
      btstack_hog_kb.c)

pico_set_program_name(picow_ble_hid_keyboard "picow_ble_hid_keyboard")
pico_set_program_version(picow_ble_hid_keyboard "0.1")

pico_enable_stdio_uart(picow_ble_hid_keyboard 1)
pico_enable_stdio_usb(picow_ble_hid_keyboard 0)

# Add the standard library to the build
target_link_libraries(picow_ble_hid_keyboard
        pico_stdlib
        pico_util
        pico_cyw43_arch_none
        pico_btstack_cyw43
        pico_btstack_ble)

# Add the standard include files to the build
target_include_directories(picow_ble_hid_keyboard PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)
pico_btstack_make_gatt_header(picow_ble_hid_keyboard PRIVATE 
  "${CMAKE_CURRENT_LIST_DIR}/picow_ble_hid_keyboard.gatt")

# Add any user requested libraries   ----------
target_link_libraries(picow_ble_hid_keyboard
        tinyusb_host 
        tinyusb_board
        )

pico_add_extra_outputs(picow_ble_hid_keyboard)


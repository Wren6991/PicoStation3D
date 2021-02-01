cmake_minimum_required(VERSION 3.12)

# Force use of our own board header, not one of the ones in the SDK (todo bit
# of a hack ask Graham if there is a better way)
set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/include/board)
set(PICO_BOARD picostation)

include(pico_sdk_import.cmake)

project(picoboy_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_compile_options(-Wall)

include_directories(include)
add_subdirectory(apps)

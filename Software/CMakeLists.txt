cmake_minimum_required(VERSION 3.6)

# set the project name
project(playback_test)



set(BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/LoRaWAN/App/inc)


set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/BSP/Components/ublox)

set(SOURCES ${BSP_DIR}/bsp.h ${MAIN_DIR}/playback.c)


# add the executable
add_executable(playback_test ${SOURCES})
add_compile_definitions(playback_testing)

target_include_directories(playback_test PUBLIC ${BSP_DIR})
target_include_directories(playback_test PUBLIC ${MAIN_DIR})



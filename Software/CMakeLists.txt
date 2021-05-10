# cmake_minimum_required(VERSION 3.6)

# # set the project name
# project(playback_test)



# set(BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/LoRaWAN/App/inc)


# set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/BSP/Components/ublox)

# set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/Third_Party/LoRaWAN/Utilities)


# set(SOURCES ${BSP_DIR}/bsp.h ${BSP_DIR}/main.h ${MAIN_DIR}/playback.c ${UTILS_DIR}/utilities.h)


# # add the executable
# add_executable(playback_test ${SOURCES})
# add_compile_definitions(playback_testing)

# target_include_directories(playback_test PUBLIC ${BSP_DIR})
# target_include_directories(playback_test PUBLIC ${MAIN_DIR})
# target_include_directories(playback_test PUBLIC ${UTILS_DIR})



cmake_minimum_required(VERSION 3.7)

project(cpputest_example)

include(CTest)

add_subdirectory(mocking)
add_subdirectory(testtools)
add_subdirectory(tests)
add_subdirectory(src)





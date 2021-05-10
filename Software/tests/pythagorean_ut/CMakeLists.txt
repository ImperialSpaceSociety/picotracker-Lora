cmake_minimum_required(VERSION 3.7)

include_directories(${CPPUTEST_SRC_DIR})
include_directories(${CPPUTESTEXT_SRC_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/mocking)
include_directories(${PROJECT_SOURCE_DIR}/Drivers/BSP/Components/ublox)


set(SOURCE_FILES
    main.cpp
    pythagorean_ut.cpp
    geofence_ut.cpp
    ${PROJECT_SOURCE_DIR}/src/pythagorean.c
    ${PROJECT_SOURCE_DIR}/Drivers/BSP/Components/ublox/geofence.c
    square_root_mock.cpp)

add_executable(pythagorean_ut ${SOURCE_FILES})
target_link_libraries(pythagorean_ut CppUTest CppUTestExt)

add_test(pythagorean_test pythagorean_ut)
cmake_minimum_required(VERSION 3.25)
project(target-firmware VERSION 0.0.1 LANGUAGES CXX C)

add_library(firmware OBJECT
    ${PROJECT_SOURCE_DIR}/drivers/src/I2c1.cpp
    ${PROJECT_SOURCE_DIR}/drivers/src/Uart2.cpp
    ${PROJECT_SOURCE_DIR}/drivers/src/Peripherals.cpp
    ${PROJECT_SOURCE_DIR}/drivers/globalISR/GlobalISR.cpp

    ${PROJECT_SOURCE_DIR}/sensors/src/MPU6050.cpp
)

target_include_directories(firmware INTERFACE
    ${PROJECT_SOURCE_DIR}/drivers/include/
    ${PROJECT_SOURCE_DIR}/sensors/include/
    ${PROJECT_SOURCE_DIR}/../system/cmsis/include/
    ${PROJECT_SOURCE_DIR}/../system/stm32f4xx/include/
)

target_include_directories(firmware PRIVATE
    ${PROJECT_SOURCE_DIR}/drivers/include/
    ${PROJECT_SOURCE_DIR}/sensors/include/
)

target_link_libraries(firmware PRIVATE system)


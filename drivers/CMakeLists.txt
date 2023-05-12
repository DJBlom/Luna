cmake_minimum_required(VERSION 3.25)
project(target-drivers VERSION 0.0.1 LANGUAGES CXX C)

add_library(drivers OBJECT
    ${PROJECT_SOURCE_DIR}/src/I2C1.cpp
    ${PROJECT_SOURCE_DIR}/src/Uart2.cpp
    ${PROJECT_SOURCE_DIR}/src/Peripherals.cpp
    ${PROJECT_SOURCE_DIR}/globalISR/GlobalISR.cpp
)

target_include_directories(drivers INTERFACE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/../system/cmsis/include/
    ${PROJECT_SOURCE_DIR}/../system/stm32f4xx/include/
)

target_include_directories(drivers PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(drivers PRIVATE system)


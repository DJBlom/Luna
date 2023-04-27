cmake_minimum_required(VERSION 3.25)
project(target-utilities VERSION 0.0.1 LANGUAGES CXX C)

add_library(utilities OBJECT
    ${PROJECT_SOURCE_DIR}/src/Uart2.cpp
    ${PROJECT_SOURCE_DIR}/src/GlobalISR.cpp
    ${PROJECT_SOURCE_DIR}/src/Peripherals.cpp
)

target_include_directories(utilities INTERFACE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/interface/
)

target_include_directories(utilities PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/interface/
)

target_link_libraries(utilities PRIVATE system)


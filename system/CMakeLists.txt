cmake_minimum_required(VERSION 3.25)
project(target-system VERSION 0.0.1 LANGUAGES CXX C)

add_library(system OBJECT
    ${PROJECT_SOURCE_DIR}/src/cmsis/system_stm32f4xx.c
)

target_include_directories(system INTERFACE
    ${PROJECT_SOURCE_DIR}/include/cmsis/
)

target_include_directories(system PRIVATE
    ${PROJECT_SOURCE_DIR}/include/cmsis/
)

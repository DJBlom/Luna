cmake_minimum_required(VERSION 3.25)
project(target-system VERSION 0.0.1 LANGUAGES CXX C)

add_library(system OBJECT
    ${PROJECT_SOURCE_DIR}/stm32f4xx/src/system_stm32f4xx.c
)

target_include_directories(system INTERFACE
    ${PROJECT_SOURCE_DIR}/cmsis/include/
    ${PROJECT_SOURCE_DIR}/stm32f4xx/include/
)

target_include_directories(system PRIVATE
    ${PROJECT_SOURCE_DIR}/cmsis/include/
    ${PROJECT_SOURCE_DIR}/stm32f4xx/include/
)

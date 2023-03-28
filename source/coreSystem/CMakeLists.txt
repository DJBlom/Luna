cmake_minimum_required(VERSION 3.25)
project(target-coreSystem VERSION 0.0.1 LANGUAGES CXX C)

add_library(coreSystem OBJECT
    ${PROJECT_SOURCE_DIR}/src/CoreSystem.c
    ${PROJECT_SOURCE_DIR}/src/CoreSystemConfiguration.c
    ${PROJECT_SOURCE_DIR}/src/CoreSystemServices.c
    ${PROJECT_SOURCE_DIR}/src/CoreSystemWatchdog.c
)

target_include_directories(coreSystem PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/../../system/include/cmsis/
    ${PROJECT_SOURCE_DIR}/../../system/include/stm32f4xx/
)

target_link_libraries(coreSystem PRIVATE middleware system)

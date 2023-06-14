cmake_minimum_required(VERSION 3.25)
project(target-coreSystem VERSION 0.0.1 LANGUAGES CXX C)

add_library(coreSystem OBJECT
    ${PROJECT_SOURCE_DIR}/src/ConfigurationCoreSystem.cpp
    ${PROJECT_SOURCE_DIR}/src/InitializeCoreSystem.cpp
    ${PROJECT_SOURCE_DIR}/src/ServicesCoreSystem.cpp
    ${PROJECT_SOURCE_DIR}/rtosISR/IsrCoreSystem.c
)

target_include_directories(coreSystem PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/../features/include/
    ${PROJECT_SOURCE_DIR}/../../drivers/include/
    ${PROJECT_SOURCE_DIR}/../../system/include/cmsis/
)

target_link_libraries(coreSystem PRIVATE features middleware system firmware)

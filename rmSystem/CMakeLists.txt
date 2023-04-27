cmake_minimum_required(VERSION 3.25)
project(target-rmSystem VERSION 0.0.1 LANGUAGES CXX C)

add_library(rmSystem OBJECT
    ${PROJECT_SOURCE_DIR}/src/RmSystemSequencer.cpp
    ${PROJECT_SOURCE_DIR}/src/RmSystemConfiguration.c
    ${PROJECT_SOURCE_DIR}/src/RmSystemServices.cpp
    ${PROJECT_SOURCE_DIR}/src/RmSystemWatchdog.c
)

target_include_directories(rmSystem PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/../source/include/
    ${PROJECT_SOURCE_DIR}/../utilities/include/
    ${PROJECT_SOURCE_DIR}/../system/include/cmsis/
    ${PROJECT_SOURCE_DIR}/../system/include/stm32f4xx/
)

target_link_libraries(rmSystem PRIVATE middleware system utilities)

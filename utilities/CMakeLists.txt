cmake_minimum_required(VERSION 3.25)
project(target-utilities VERSION 0.0.1 LANGUAGES CXX C)

add_library(utilities OBJECT
    ${PROJECT_SOURCE_DIR}/src/Logger.cpp
)

target_include_directories(utilities INTERFACE
    ${PROJECT_SOURCE_DIR}/include/
)

target_include_directories(utilities PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(utilities PRIVATE system)


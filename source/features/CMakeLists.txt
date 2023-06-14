cmake_minimum_required(VERSION 3.25)
project(target-features VERSION 0.0.1 LANGUAGES CXX C)

add_library(features OBJECT
    ${PROJECT_SOURCE_DIR}/src/Logger.cpp
)

target_include_directories(features PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
)

target_link_libraries(features PRIVATE firmware)

cmake_minimum_required(VERSION 3.25)
project(target-middleware VERSION 0.0.1 LANGUAGES CXX C ASM)

set(MIDDLEWARE_INCLUDE
    ${PROJECT_SOURCE_DIR}/ 
    ${PROJECT_SOURCE_DIR}/freertos/include/
    ${PROJECT_SOURCE_DIR}/freertos/portable/GCC/ARM_CM4F/
)

add_library(middleware STATIC
    ${PROJECT_SOURCE_DIR}/freertos/croutine.c
    ${PROJECT_SOURCE_DIR}/freertos/event_groups.c
    ${PROJECT_SOURCE_DIR}/freertos/list.c
    ${PROJECT_SOURCE_DIR}/freertos/queue.c
    ${PROJECT_SOURCE_DIR}/freertos/tasks.c
    ${PROJECT_SOURCE_DIR}/freertos/timers.c
    ${PROJECT_SOURCE_DIR}/freertos/portable/MemMang/heap_1.c
    ${PROJECT_SOURCE_DIR}/freertos/portable/GCC/ARM_CM4F/port.c
)

target_include_directories(middleware INTERFACE
    ${MIDDLEWARE_INCLUDE}
)

target_include_directories(middleware PRIVATE
    ${MIDDLEWARE_INCLUDE}
)

target_link_libraries(middleware PRIVATE system)

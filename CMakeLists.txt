cmake_minimum_required(VERSION 3.25)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(Luna VERSION 0.0.1 LANGUAGES CXX C ASM)

option(USE_RTOS "Enable RTOS support" OFF)
option(BUILD_LUNA "Building Luna" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmakeModules)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(BUILD_LUNA)
    add_compile_options(
        -Wall
        -Werror
        -Wextra
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-Og>
    )

    add_compile_definitions(
        $<$<CONFIG:DEBUG>:DEBUG>
        $<$<CONFIG:DEBUG>:TRACE_ENABLED>
        $<$<BOOL:${USE_RTOS}>:RTOS>
        $<$<BOOL:${BUILD_LUNA}>:LUNA>
    )

    add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/startup/startup_stm32f411xe.s
        ${CMAKE_SOURCE_DIR}/source/main.cpp
        ${CMAKE_SOURCE_DIR}/source/src/Logger.cpp
    )

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/utilities/include/
        ${CMAKE_SOURCE_DIR}/system/include/stm32f4xx/
        ${CMAKE_SOURCE_DIR}/rmSystem/include/
        ${CMAKE_SOURCE_DIR}/source/include/
        ${CMAKE_SOURCE_DIR}/source/
    )

    set(LINKER_SCRIPTS
        ${CMAKE_SOURCE_DIR}/startup/STM32F411RETx_FLASH.ld
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES 
        SUFFIX .elf
        LINK_DEPENDS "${LINKER_SCRIPTS}"
    )

    target_link_options(${PROJECT_NAME} PRIVATE
        -T${LINKER_SCRIPTS}
        LINKER:--print-memory-usage
        LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
    )

    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/rmSystem)
        add_subdirectory(rmSystem)
        target_link_libraries(${PROJECT_NAME} PRIVATE rmSystem)
    endif()

    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/utilities)
        add_subdirectory(utilities)
        target_link_libraries(${PROJECT_NAME} PRIVATE utilities)
    endif()

    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/system)
        add_subdirectory(system)
        target_link_libraries(${PROJECT_NAME} PRIVATE system)
    endif()

    if (USE_RTOS AND IS_DIRECTORY ${CMAKE_SOURCE_DIR}/middleware)
        add_subdirectory(middleware)
        target_link_libraries(${PROJECT_NAME} PRIVATE middleware)
    endif()


    if (EXISTS ${CMAKE_OBJCOPY})
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}>
                    ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${PROJECT_NAME}>.hex
        )
    else ()
        message(STATUS "'objcopy' not found: cannot generate .hex file")
    endif()

    if (EXISTS "${TOOLCHAIN_SIZE}")
        add_custom_command(
            TARGET ${PROJECT_NAME} 
            POST_BUILD
            COMMAND ${TOOLCHAIN_SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}>
                    >${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${PROJECT_NAME}>.bsz
        )

        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${TOOLCHAIN_SIZE} --format=sysv -x $<TARGET_FILE:${PROJECT_NAME}>
                    >${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_NAME:${PROJECT_NAME}>.ssz
        )
    else()
        message(STATUS "'size' not found: cannot generate .[bs]sz files")
    endif()
endif()





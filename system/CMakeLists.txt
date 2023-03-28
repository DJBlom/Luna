cmake_minimum_required(VERSION 3.25)
project(target-system VERSION 0.0.1 LANGUAGES CXX C)

add_library(system OBJECT
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_cortex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_dma.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_dma_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_exti.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_flash.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_flash_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_flash_ramfunc.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_gpio.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_iwdg.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_pwr.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_pwr_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_rcc.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_rcc_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_rtc.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_rtc_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_tim.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_tim_ex.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/stm32f4xx_hal_uart.c
    ${PROJECT_SOURCE_DIR}/src/stm32f4xx/system_stm32f4xx.c
)

target_include_directories(system INTERFACE
    ${PROJECT_SOURCE_DIR}/include/cmsis/
)

target_include_directories(system PRIVATE
    ${PROJECT_SOURCE_DIR}/include/cmsis/
    ${PROJECT_SOURCE_DIR}/include/stm32f4xx/
)

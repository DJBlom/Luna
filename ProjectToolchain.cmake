set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION Cotex-M4-STM32F411RE)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CROSS_GCC_PATH /usr)
find_program(CROSS_GCC_PATH/bin "arm-none-eabi-g++")
if (NOT CROSS_GCC_PATH)
  message(FATAL_ERROR "Cannot find ARM GCC compiler: arm-none-eabi-g++")
endif()
get_filename_component(TOOLCHAIN ${CROSS_GCC_PATH} PATH)
set(TOOLCHAIN ${CROSS_GCC_PATH}/bin)
set(CMAKE_C_COMPILER ${TOOLCHAIN}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN}/arm-none-eabi-g++)
set(TOOLCHAIN_AS ${TOOLCHAIN}/arm-none-eabi-as CACHE STRING "arm-none-eabi-as")
set(TOOLCHAIN_LD ${TOOLCHAIN}/arm-none-eabi-ld CACHE STRING "arm-none-eabi-ld")
set(TOOLCHAIN_SIZE ${TOOLCHAIN}/arm-none-eabi-size CACHE STRING "arm-none-eabi-size")


set(MACHINE_ARCHITECTURE cortex-m4)
set(ARM_OPTIONS 
    -mcpu=${MACHINE_ARCHITECTURE} 
    -mthumb
    -mlittle-endian
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

add_compile_options(
    ${ARM_OPTIONS}
    -fmessage-length=0
    -funsigned-char
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -MMD
    -MP
)

add_compile_definitions(
    STM32F411xE
    USE_FULL_ASSERT
    $<$<CONFIG:DEBUG>:DEBUG>
)

add_link_options(
    ${ARM_OPTIONS}
    $<$<CONFIG:DEBUG>:--specs=nosys.specs>
    $<$<CONFIG:DEBUG>:-u_printf_float>
    $<$<CONFIG:DEBUG>:-u_scanf_float>
    LINKER:--build-id
    LINKER:--gc-sections
)


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

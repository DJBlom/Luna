/********************************************************************************
 * Contents: The main function
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: 
 *******************************************************************************/
#include "InitializeCoreSystem.h"
#include "Peripherals.h"
#include "Logger.h"
#include "Uart2.h"
#include "I2C1.h"


#include "stm32f411xe.h"




constexpr std::uint8_t mainSlaveAddress{0xD0};
constexpr std::uint8_t outSlaveAddress{0x1C};
constexpr std::uint8_t whoAmi{0x75};

std::uint8_t* buffer{0};




int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    Comm::I2c1 i2c1;

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);
    Comm::Uart2 uart2;
    System::Logger logger{"System: "};
//    logger.LogMessage(uart2, "Restarted \n\n\r");



//    std::uint8_t* deviceAddress = i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//    logger.LogMessage(uart2, "Device Found: %x \n\n\r", *deviceAddress);
    for (int i = 0; i < 500000; i++)
    {
    }

    // Power
    buffer = 0;
    i2c1.Write(mainSlaveAddress, 0x6B, buffer, 1);
    for (int i = 0; i < 500000; i++)
    {
    }

//    // Sample rate
//    buffer = (std::uint8_t*)0x07;
//    i2c1.Write(mainSlaveAddress, 0x19, buffer, 1);
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//
//    // Config gyro
//    buffer = 0x00;
//    i2c1.Write(mainSlaveAddress, 0x1A, buffer, 1);
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//
//    std::uint8_t* data = i2c1.Read(mainSlaveAddress, 0x43, buffer, 6);
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//
//    std::uint16_t x = (std::int16_t)(data[0] << 8 | data[1]);
//    std::uint16_t y = (std::int16_t)(data[2] << 8 | data[3]);
//    std::uint16_t z = (std::int16_t)(data[4] << 8 | data[5]);
//
//    logger.LogMessage(uart2, "X, Y, Z: %x \n\n\r", (x / 131), (y / 131), (z / 131));


//    std::uint8_t* data = (std::uint8_t*)"c";

    // I2C1 Transfer function
    while (1)
    {
//        i2c1.Write(mainSlaveAddress, outSlaveAddress, data, 1);

        for (int i = 0; i < 50000; i++)
        {

        }


//        i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);
    }


    
//    Comm::Uart2 uart2;
//    System::Logger logger{"System: "};
//    logger.LogMessage(uart2, "Restarted \n\n\r");
//
//    if (CoreSystemInitialized())
//    {
//        if (SystemServicesCreated())
//        {
//            vTaskStartScheduler();
//        }
//        else
//        {
//            logger.LogMessage(uart2, "Service Creation FAILED \n\n\r");
//        }
//    }
//    else
//    {
//        logger.LogMessage(uart2, "Initialization FAILED \n\n\r");
//    }

    return 0;
}


























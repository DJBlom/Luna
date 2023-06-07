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

std::int16_t* buffer{0};







int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    Comm::I2c1 i2c1;

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);
    Comm::Uart2 uart2;
    System::Logger logger{"System: "};
    logger.LogMessage(uart2, "Restarted \n\n\r");
    for (int i = 0; i < 500000; i++)
    {
    }



//    std::int16_t* data =  i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);
    
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//    logger.LogMessage(uart2, "Device Found: %x \n\n\r", *deviceAddress);
//    for (int i = 0; i < 500000; i++)
//    {
//    }

    // Power
//    i2c1.Write(mainSlaveAddress, 0x6B, buffer, 2);
//    for (int i = 0; i < 10000; i++)
//    {
//    }

//    // Sample rate
//    buffer[0] = 0x07;
//    i2c1.Write(mainSlaveAddress, 0x19, buffer, 1);
//    for (int i = 0; i < 500000; i++)
//    {
//    }
//
//    // Config gyro
//    buffer[0] = 0x00;
//    i2c1.Write(mainSlaveAddress, 0x1A, buffer, 1);
//    for (int i = 0; i < 500000; i++)
//    {
//    }

//    GPIOA->ODR = GPIOA->ODR | (1U << 5);
//    data = i2c1.Read(mainSlaveAddress, 0x43, buffer, 6);
//    std::int16_t x = (std::int16_t)(data[0] << 8 | data[1]);
//    std::int16_t y = (std::int16_t)(data[2] << 8 | data[3]);
//    std::int16_t z = (std::int16_t)(data[4] << 8 | data[5]);
//
//    logger.LogMessage(uart2, "X = %d, Y = %d, Z = %d \n\n\r", (x / 131), (y / 131), (z / 131));

    i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);
    for (int i = 0; i < 500000; i++)
    {
    }
    i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);

    std::int32_t dataTransferred = 0xffff - DMA_SxNDT;

    logger.LogMessage(uart2, "Data returned from MPU 6050: %x | Number of Data Items Transferred: %d \n\n\r", buffer[0], dataTransferred);

    while (1)
    {
    //    i2c1.Read(mainSlaveAddress, whoAmi, buffer, 1);
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


























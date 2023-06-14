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
#include "MPU6050.h"
#include "I2c1.h"


#include "stm32f411xe.h"












int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    Comm::I2c1 i2c1;
    Sensor::MPU6050 mpu6050;
    mpu6050.Initialize(i2c1);

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);
    Comm::Uart2 uart2;
    System::Logger logger{"System: "};
    logger.LogMessage(uart2, "Restarted \n\n\r");
    for (int i = 0; i < 500000; i++)
    {
    }





    std::int8_t* data{nullptr};
    std::int16_t x{0};
    std::int16_t y{0};
    std::int16_t z{0};  
    while (1)
    {
        data = mpu6050.ReadGyrometerData(i2c1);
        x = (std::int16_t)(data[0] << 8 | data[1]);
        y = (std::int16_t)(data[2] << 8 | data[3]);
        z = (std::int16_t)(data[4] << 8 | data[5]);
        logger.LogMessage(uart2, "X = %d, Y = %d, Z = %d \n\n\r", (x / 131), (y / 131), (z / 131));
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


























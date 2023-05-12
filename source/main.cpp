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




constexpr std::uint8_t mainSlaveAddress{0x68};
constexpr std::uint8_t outSlaveAddress{0x3B};




int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    Comm::I2c1 i2c1;

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);




//    std::uint8_t* data = (std::uint8_t*)"c";
//
//    // I2C1 Transfer function
//    while (1)
//    {
//        i2c1.Write(mainSlaveAddress, data, 1);
//
//        for (int i = 0; i < 50000; i++)
//        {
//
//        }
//
//        i2c1.Read(mainSlaveAddress, outSlaveAddress, data, 1);
//    }


    
//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;
//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_STOP;

//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;
//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_PEC;
//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_POS;

//


//    I2C1->CR2 = I2C1->CR2 | I2C_CR2_ITEVTEN;
//    I2C1->CR2 = I2C1->CR2 | I2C_CR2_ITBUFEN;



    Comm::Uart2 uart2;
    System::Logger logger{"System: "};
    logger.LogMessage(uart2, "Restarted \n\n\r");

    if (CoreSystemInitialized())
    {
        if (SystemServicesCreated())
        {
            vTaskStartScheduler();
        }
        else
        {
            logger.LogMessage(uart2, "Service Creation FAILED \n\n\r");
        }
    }
    else
    {
        logger.LogMessage(uart2, "Initialization FAILED \n\n\r");
    }

    return 0;
}


























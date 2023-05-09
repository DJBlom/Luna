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


#include "stm32f411xe.h"








int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);


    // Configure GPIOB
    GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODER8_0; 
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER8_1; 

    GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODER9_0; 
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER9_1; 

    // Configure open-drain for both GPIO 8 and 9.
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT8;
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT9;

    // Configure high speed.
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED8_1;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED9_1;

    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL8_0;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL8_1;
    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL8_2;
    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL8_3;

    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL9_0;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL9_1;
    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL9_2;
    GPIOB->AFR[1] = GPIOB->AFR[1] & ~GPIO_AFRH_AFSEL9_3;

    // Configure the DMA 
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_CHSEL_1;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_MINC;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_DIR_0;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_TCIE;

    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_CHSEL_1;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_MINC;
    DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_DIR_0;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_TCIE;

    // General Initialization of I2C1
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_NOSTRETCH;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ENGC;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_DMAEN;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_FREQ_5;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_LAST;
    I2C1->CCR = I2C1->CCR | I2C_CCR_CCR;
    I2C1->TRISE = I2C1->TRISE | I2C_TRISE_TRISE;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_PE;


    // I2C1 Transfer
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


























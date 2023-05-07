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
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_PINC;
    DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_DIR_0;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_TCIE;

    // Configure I2C1 


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


























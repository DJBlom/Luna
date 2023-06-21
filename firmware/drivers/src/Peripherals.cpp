/********************************************************************************
 * Contents: Peripherals class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file implements all the methods defined in the Peripherals class.
 *******************************************************************************/
#include "Peripherals.h"


void System::Peripherals::Initialize()
{
    RccInitialization();
    EnableIRQHandlers();
}


void System::Peripherals::RccInitialization()
{
    // GPIOs
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOBEN;

    // DMAs
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_DMA1EN;

    // COMMs
    RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_I2C1EN; 
    RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_USART2EN; 
}


void System::Peripherals::EnableIRQHandlers()
{
    NVIC_SetPriority(DMA1_Stream6_IRQn, 2);
    NVIC_SetPriority(DMA1_Stream5_IRQn, 0);

    NVIC_EnableIRQ(DMA1_Stream6_IRQn);
    NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

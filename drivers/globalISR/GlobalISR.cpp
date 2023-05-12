/********************************************************************************
 * Contents: Global ISRs
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file implements all the global interrupt service routines for all
 * the stm32 f411re nucleo board that is used in the application. Furthermore,
 * it's wrapped in a extern "C" clause so that the C++ compiler can see it.
 *******************************************************************************/
#include "stm32f411xe.h"


extern "C" 
{
    void DMA1_Stream6_IRQHandler()
    {
        if (DMA1->HISR & DMA_HISR_TCIF6)
        {
            DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF6;
            DMA1_Stream6->CR = DMA1_Stream6->CR & ~DMA_SxCR_EN;
        }
    }

    void DMA1_Stream5_IRQHandler()
    {
        if (DMA1->HISR & DMA_HISR_TCIF5)
        {
            I2C1->CR1 = I2C1->CR1 | I2C_CR1_STOP;
            DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF5;
            DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_EN;
        }
    }
}

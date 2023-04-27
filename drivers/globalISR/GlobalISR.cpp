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
}

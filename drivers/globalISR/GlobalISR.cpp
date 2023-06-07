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
#include "DeviceAddresses.h"

std::uint8_t registerAddress[3]{0};
std::uint8_t i2cTx{0};
std::uint8_t count{0};

extern "C" 
{
    void DMA1_Stream7_IRQHandler()
    {
        if (DMA1->HISR & DMA_HISR_TCIF7)
        {
            DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF7;
            DMA1_Stream7->CR = DMA1_Stream7->CR & ~DMA_SxCR_EN;
        }
    }

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
            GPIOA->ODR = GPIOA->ODR & ~(1U << 5);
            DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF5;
            DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_EN;
            I2C1->CR1 = I2C1->CR1 | I2C_CR1_STOP;
        }
    }

    void I2C1_EV_IRQHandler()
    {
//        if (i2cTx == 1)
//        {
//            if (I2C1->SR1 & I2C_SR1_SB)
//            {
//                // Will need a an include file that specifies this address
//                I2C1->DR = registerAddress[0];
//            }
//            else if (I2C1->SR1 & I2C_SR1_ADDR)
//            {
//                I2C1->SR2;
//
//                // Will need a an include file that specifies this address
//                I2C1->DR = registerAddress[1];
//            }
//            else if (I2C1->SR1 & I2C_SR1_TXE)
//            {
//                DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_EN;
//            }
//        }
//        else
//        {
            if (I2C1->SR1 & I2C_SR1_SB) // EV5
            {
                I2C1->DR = registerAddress[0];
            }
            else if (I2C1->SR1 & I2C_SR1_ADDR) // EV6
            {
                I2C1->SR2;

//                I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ACK;
//
//                if (count != 0)
//                {
//                    count = 0;
//                }
//                else
//                {
//                    count++;
                    I2C1->DR = registerAddress[1];
//                }
            }
//            else if (I2C1->SR1 & I2C_SR1_BTF)
//            {
//                I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;
//                registerAddress[0] = registerAddress[2];
//            }
//        }
    }
}

/********************************************************************************
 * Contents: Uart2 class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file implements all the methods defined in the Uart2 class.
 *******************************************************************************/
#include "Uart2.h"

Comm::Uart2::Uart2()
{
    this->dataLength = 0;
    Uart2Initialize();
    Dma1Initialize();
    GpioInitialize();
}


bool Comm::Uart2::Transmit(const char* data)
{
    bool isTransmitted{true};
    if (TransmissionIsComplete() && DataIsInBounds(data))
    {
        if(LoadData(data))
        {
            DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_EN;
        }
    }

    return isTransmitted;
}


bool Comm::Uart2::TransmissionIsComplete()
{
    bool transferComplete{false};
    if (USART2->SR & USART_SR_TC) 
    {
        transferComplete = true;
    }

    return transferComplete;
}


bool Comm::Uart2::LoadData(const char* data)
{
    bool isDataLoaded{false};
    DMA1_Stream6->M0AR = (std::uint32_t)data;
    DMA1_Stream6->PAR = (std::uint32_t)&USART2->DR;
    DMA1_Stream6->NDTR = this->dataLength;
    if (USART2->SR & USART_SR_TXE)
    {
        isDataLoaded = true;
    }

    return isDataLoaded;
}


bool Comm::Uart2::DataIsInBounds(const char* data)
{
    bool isInBounds{false};
    if ((data != nullptr) && 
        (std::strlen(data) < UART2::UPPERBOUND) && 
        (std::strlen(data) > UART2::LOWERBOUND))
    {
        this->dataLength = std::strlen(data);
        isInBounds = true;
    }

    return isInBounds; 
}


void Comm::Uart2::Uart2Initialize()
{
    USART2->BRR = UART2::BAUDRATE; 
    USART2->CR1 = USART2->CR1 | USART_CR1_OVER8;
    USART2->CR3 = USART2->CR3 | USART_CR3_DMAT;
    USART2->CR1 = USART2->CR1 | USART_CR1_TE;
    USART2->CR1 = USART2->CR1 | USART_CR1_UE;
}


void Comm::Uart2::Dma1Initialize()
{
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_CHSEL_2;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_MINC;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_DIR_0;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_TCIE;
}


void Comm::Uart2::GpioInitialize()
{
    GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODER2_0;
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER2_1;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_0;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_1;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_2;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] & ~GPIO_AFRL_AFSEL2_3;
}




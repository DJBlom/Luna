#include "Logger.h"
System::Logger::Logger()
{
    LoggerSetup("System: ");
}


System::Logger::Logger(const char* messagePrefix)
{
    LoggerSetup(messagePrefix);
}


bool System::Logger::LogMessage(const char* userMessage, ...)
{
    bool messageLogged{false};
    std::va_list args;
    va_start(args, userMessage);
    std::strncpy(this->message, this->prefix, BUFFERSIZE - 1);
    std::strncat(this->message, userMessage, BUFFERSIZE - 1);
    std::strncat(this->message, "\n\r", BUFFERSIZE - 1);
    std::vsnprintf(this->buffer, BUFFERSIZE, this->message, args);
    va_end(args);

    
    DMA1_Stream6->M0AR = (uint32_t)this->buffer;
    DMA1_Stream6->PAR = (uint32_t)&USART2->DR;
    DMA1_Stream6->NDTR = (uint8_t)strlen(this->buffer);
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_EN;
    if ((TransferIsComplete()) == true)
    {
        DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF6;
        DMA1_Stream6->CR = DMA1_Stream6->CR & ~DMA_SxCR_EN;
        messageLogged = true;
    }
 
    return messageLogged;
}



void System::Logger::LoggerSetup(const char* messagePrefix)
{
    if (messagePrefix == nullptr)
    {
        this->prefix = "System: ";
    }
    else
    {
        this->prefix = messagePrefix;
    }

    GpioConfigure();
    UartConfigure();
    DmaConfigure();
    memset(this->message, 0, BUFFERSIZE);
    memset(this->buffer, 0, BUFFERSIZE);
}


void System::Logger::GpioConfigure()
{
    GPIOA->MODER = GPIOA->MODER & ~GPIO_MODER_MODER2_0;
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER2_1;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_0;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_1;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] | GPIO_AFRL_AFSEL2_2;
    GPIOA->AFR[UART2::GPIO_ALT] = GPIOA->AFR[UART2::GPIO_ALT] & ~GPIO_AFRL_AFSEL2_3;

}


void System::Logger::UartConfigure()
{
    USART2->BRR = UART2::BAUDRATE; 
    USART2->CR1 = USART2->CR1 | USART_CR1_OVER8;
    USART2->CR1 = USART2->CR1 & ~USART_CR1_M;
    USART2->CR2 = USART2->CR2 & ~USART_CR2_STOP;
    USART2->CR3 = USART2->CR3 | USART_CR3_DMAT;
    USART2->CR1 = USART2->CR1 | USART_CR1_TE;
    USART2->CR1 = USART2->CR1 | USART_CR1_UE;
}


void System::Logger::DmaConfigure()
{
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_CHSEL_1;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_MINC;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_DIR_0;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_TCIE;
}


bool System::Logger::TransferIsComplete()
{
    bool transferComplete{false};
    while ((DMA1->HISR & DMA_HISR_TCIF6) == 0){}
    transferComplete = true;

    return transferComplete;
}

//extern "C" void DMA1_Stream6_IRQHandler(void)
//{
//    if (DMA1->HISR & DMA_HISR_TCIF6)
//    {
//        DMA1->HIFCR = DMA1->HIFCR | DMA_HIFCR_CTCIF6;
//        DMA1_Stream6->CR = DMA1_Stream6->CR & ~DMA_SxCR_EN;
//    }
//}









#include "I2C1.h"





Comm::I2c1::I2c1()
{
    GpioInitialize();
    Dma1Initialize();
    I2C1Initialize();
}


bool Comm::I2c1::LineIsBusy()
{
    return (I2C1->SR2 & I2C_SR2_BUSY);
}


void Comm::I2c1::StartCommunication()
{
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;
    while ((I2C1->SR1 & I2C_SR1_SB) == false) {}
}


void Comm::I2c1::AddressTransmission(std::uint8_t address)
{
    I2C1->DR = address;
    while ((I2C1->SR1 & I2C_SR1_ADDR) == false) {}
    I2C1->SR2;
}


void Comm::I2c1::RegisterTransmission(std::uint8_t address)
{
    while ((I2C1->SR1 & I2C_SR1_TXE) == false) {}
    I2C1->DR = address;
    while ((I2C1->SR1 & I2C_SR1_TXE) == false) {}
}


bool Comm::I2c1::WriteDMA(std::int8_t data, std::uint8_t len)
{
    bool dmaWriteSuccess{false};
    if (LengthInBounds(len))
    {
        DMA1_Stream7->M0AR = (std::uint32_t)data;
        DMA1_Stream7->PAR = (std::uint32_t)&I2C1->DR;
        DMA1_Stream7->NDTR = len; 
        DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_EN;
        dmaWriteSuccess = true;
    }

    return dmaWriteSuccess;
}


std::int8_t* Comm::I2c1::ReadDMA(std::int8_t len)
{
    static std::int8_t temp[I2CBUFFERSIZE]{0};
    if (LengthInBounds(len))
    {
        while ((I2C1->SR1 & I2C_SR1_RXNE) == false) {}
        DMA1_Stream5->M0AR = (std::uint32_t)temp;
        DMA1_Stream5->PAR = (std::uint32_t)&I2C1->DR;
        DMA1_Stream5->NDTR = len;
        DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_EN;
    }

    return temp;
}


void Comm::I2c1::DisableAcknowledgement()
{
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ACK;
}


bool Comm::I2c1::LengthInBounds(std::int8_t len)
{
    bool lengthInBounds{true};
    if (len >= Bounds::upperBound)
    {
        lengthInBounds = false; 
    }
    else if (len <= Bounds::lowerBound)
    {
        lengthInBounds = false;
    }

    return lengthInBounds;
}


void Comm::I2c1::I2C1Initialize()
{
    // General Initialization of I2C1
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_PE;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_NOSTRETCH;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ENGC;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_FREQ_4;
    I2C1->CCR = I2C1->CCR & ~I2C_CCR_FS;
    I2C1->CCR = I2C1->CCR & ~I2C_CCR_DUTY;

    I2C1->CCR = I2C1->CCR | Config::ccr;
    I2C1->TRISE = Config::trise;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_LAST;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_DMAEN;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_PE;
}


void Comm::I2c1::Dma1Initialize()
{
    // Configure the DMA transmit
    DMA1_Stream7->CR = DMA1_Stream7->CR & ~DMA_SxCR_EN;
    DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_CHSEL_0;
    DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_MINC;
    DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_DIR_0;
    DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_PL_0;
    DMA1_Stream7->CR = DMA1_Stream7->CR | DMA_SxCR_TCIE;

    // Configure the DMA receiver
    DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_EN;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_CHSEL_0;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_MINC;
    DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_DIR;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_PL_1;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_TCIE;
}


void Comm::I2c1::GpioInitialize()
{
    // Mode for 8 and 9
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER8_1; 
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER9_1; 

    // Output type for 8 and 9
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT8;
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT9;

    // Output speed for 8 and 9
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED8;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED9;
    
    GPIOB->PUPDR = GPIOB->PUPDR & ~GPIO_PUPDR_PUPD8_Msk;  
    GPIOB->PUPDR = GPIOB->PUPDR & ~GPIO_PUPDR_PUPD9_Msk;  

    // Alernative function for 8 and 9
    GPIOB->AFR[Config::gpioAlt] = GPIOB->AFR[Config::gpioAlt] | GPIO_AFRH_AFSEL8_2;
    GPIOB->AFR[Config::gpioAlt] = GPIOB->AFR[Config::gpioAlt] | GPIO_AFRH_AFSEL9_2;
}

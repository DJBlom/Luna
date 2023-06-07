






#include "I2C1.h"




Comm::I2c1::I2c1()
{
    GpioInitialize();
    Dma1Initialize();
    I2C1Initialize();
}


bool Comm::I2c1::Write(std::uint8_t slaveAddress, std::uint8_t address, std::int16_t* data, std::uint16_t len)
{
    bool writeSuccess{false};
    i2cTx = 1;

    // Wait till the line is not busy
    if ((I2C1->SR2 & I2C_SR2_BUSY) == 0)
    {
        registerAddress[0] = slaveAddress;
        registerAddress[1] = address;

        DMA1_Stream7->M0AR = (std::uint32_t)data;
        DMA1_Stream7->PAR = (std::uint32_t)&I2C1->DR;
        DMA1_Stream7->NDTR = len;

        I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;
    }
    writeSuccess = true;

    return writeSuccess;
}


void Comm::I2c1::Read(std::uint8_t slaveAddress, std::uint8_t address, std::int16_t* data, std::uint16_t len)
{
    i2cTx = 0;
    if ((I2C1->SR2 & I2C_SR2_BUSY) == 0)
    {
        GPIOA->ODR = GPIOA->ODR | (1U << 5);
        registerAddress[0] = slaveAddress;
        registerAddress[1] = address;
        registerAddress[2] = slaveAddress + 1;

        DMA1_Stream5->M0AR = (std::uint32_t)data;
        DMA1_Stream5->PAR = (std::uint32_t)&I2C1->DR;
        DMA1_Stream5->NDTR = len;
//        len++;
//        data++;


        Start();
        SendAddress(slaveAddress);
        SendRegAddress(address);


        Start();
        I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ACK;

        SendAddress(slaveAddress + 1);




        while ((I2C1->SR1 & I2C_SR1_RXNE) == 0) {}
        DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_EN;
//        I2C1->CR1 = I2C1->CR1 | I2C_CR1_STOP;
//        GPIOA->ODR = GPIOA->ODR ^ (1U << 5);
    }
}

void Comm::I2c1::Start()
{
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;
    while ((I2C1->SR1 & I2C_SR1_SB) == 0) {}
}

void Comm::I2c1::SendRegAddress(std::uint8_t address)
{
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0) {}
    I2C1->DR = address;
    while ((I2C1->SR1 & I2C_SR1_TXE) == 0) {}
}

void Comm::I2c1::SendAddress(std::uint8_t address)
{
    I2C1->DR = address;
    while ((I2C1->SR1 & I2C_SR1_ADDR) == 0) {}
    I2C1->SR2;
}

void Comm::I2c1::Stop()
{
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_STOP;
}
            

void Comm::I2c1::I2C1Initialize()
{
    // General Initialization of I2C1
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_PE;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_NOSTRETCH;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ENGC;
//    I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_FREQ_4;
    I2C1->CCR = I2C1->CCR & ~I2C_CCR_FS;
    I2C1->CCR = I2C1->CCR & ~I2C_CCR_DUTY;

    I2C1->CCR = I2C1->CCR | (80 << 0);
    I2C1->TRISE = 17U;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_LAST;
//    I2C1->CR2 = I2C1->CR2 | I2C_CR2_ITEVTEN;
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
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL8_2;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL9_2;
}

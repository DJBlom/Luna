






#include "I2C1.h"



Comm::I2c1::I2c1()
{
    I2C1Initialize();
    Dma1Initialize();
    GpioInitialize();
}


bool Comm::I2c1::Write(std::uint8_t slaveAddress, std::uint8_t* data, std::uint16_t len)
{
    std::uint32_t temp{0};
    // Wait till the line is not busy
    while ((I2C1->SR2 & I2C_SR2_BUSY));
        
    // Send the start bit.
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;

    // Wait till the start bit was generated
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Read to clear flags
    temp = I2C1->SR1;

    //Send slave address as a "Write" (I still need to get the slave address from sensor)
    I2C1->DR = (slaveAddress << 1 | 0);

    // Wait for address flag to be set
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // Read to clear flags
    temp = I2C1->SR1;

    // Read to clear flags
    temp = I2C1->SR2;

    temp++;

    DmaWrite(data, len);


    return true;
}


std::uint8_t* Comm::I2c1::Read(std::uint8_t slaveAddress, std::uint8_t registerAddress, std::uint8_t* data, std::uint16_t len)
{
    std::uint32_t temp{0};

    // Wait till the line is not busy
    while (I2C1->SR2 & I2C_SR2_BUSY);
        
    // Send the start bit.
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;

    // Wait till the start bit was generated
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Read to clear flags
    temp = I2C1->SR1;

    //Send slave address as a "Write" (I still need to get the slave address from sensor)
    I2C1->DR = (slaveAddress << 1 | 0);

    // Wait for address flag to be set
    while (!(I2C1->SR1 & I2C_SR1_ADDR));

    // Read to clear flags
    temp = I2C1->SR1;

    // Read to clear flags
    temp = I2C1->SR2;

    // Wait till the transfer is finished
    while (!(I2C1->SR1 & I2C_SR1_TXE));

    if (len >= 2)
    {
        // Send the ACK
        I2C1->CR1 = I2C1->CR1 | I2C_CR1_ACK;

        // Don't know where to get this yet.
        I2C1->DR = registerAddress;
    }
    else 
    {
        I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ACK;

        // Don't know where to get this yet.
        I2C1->DR = registerAddress;
    }

    while (!(I2C1->SR1 & I2C_SR1_BTF));

    // Restart 
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_START;

    // Wait till the start bit was generated
    while (!(I2C1->SR1 & I2C_SR1_SB));

    // Read to clear flags
    temp = I2C1->SR1;

    // Send slave address with a "read" (don't know the address yet)
    I2C1->DR = slaveAddress << 1 | 1;

    // Wait for address flag to be set
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    
    // use Dma to read.
    DmaRead(data, len);

    // Read to clear flags
    temp = I2C1->SR1;

    // Read to clear flags
    temp = I2C1->SR2;

    temp++;

    return data;
}


bool Comm::I2c1::DmaWrite(std::uint8_t* data, std::uint32_t len)
{
    DMA1_Stream6->M0AR = (std::uint32_t)data;
    DMA1_Stream6->PAR = (std::uint32_t)&I2C1->DR;
    DMA1_Stream6->NDTR = (std::uint8_t)len;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_EN;

    return true;
}


bool Comm::I2c1::DmaRead(std::uint8_t* data, std::uint32_t len)
{
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_CHSEL_0;
    DMA1_Stream6->M0AR = (std::uint32_t)data;
    DMA1_Stream6->PAR = (std::uint32_t)&I2C1->DR;
    DMA1_Stream6->NDTR = (std::uint8_t)len;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_EN;

    return true;
}


void Comm::I2c1::I2C1Initialize()
{
    // General Initialization of I2C1
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_PE;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_SWRST;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_NOSTRETCH;
    I2C1->CR1 = I2C1->CR1 & ~I2C_CR1_ENGC;
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_DMAEN;
    I2C1->CR2 = I2C1->CR2 | (45 << 0); //I2C_CR2_FREQ_5;
    I2C1->CCR = (255 << 0); 
    I2C1->CR2 = I2C1->CR2 | I2C_CR2_LAST;
    I2C1->CCR = I2C1->CCR | I2C_CCR_CCR;
    I2C1->TRISE = 46; //I2C_TRISE_TRISE;
    I2C1->CR1 = I2C1->CR1 | I2C_CR1_PE;
}


void Comm::I2c1::Dma1Initialize()
{
    // Configure the DMA transmit
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_MINC;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_DIR_0;
    DMA1_Stream6->CR = DMA1_Stream6->CR | DMA_SxCR_TCIE;

    // Configure the DMA receiver
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_CHSEL_1;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_MINC;
    DMA1_Stream5->CR = DMA1_Stream5->CR & ~DMA_SxCR_DIR;
    DMA1_Stream5->CR = DMA1_Stream5->CR | DMA_SxCR_TCIE;
}


void Comm::I2c1::GpioInitialize()
{
    // Mode for 8 and 9
//    GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODER8_0; 
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER8_1; 

//    GPIOB->MODER = GPIOB->MODER & ~GPIO_MODER_MODER9_0; 
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER9_1; 

    // Output type for 8 and 9
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT8;
    GPIOB->OTYPER = GPIOB->OTYPER | GPIO_OTYPER_OT9;

    // Output speed for 8 and 9
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED8_Msk;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED9_Msk;
    
    GPIOB->PUPDR = GPIOB->PUPDR & ~GPIO_PUPDR_PUPD8_Msk;  
    GPIOB->PUPDR = GPIOB->PUPDR & ~GPIO_PUPDR_PUPD9_Msk;  

    // Alernative function for 8 and 9
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL8_2;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFSEL9_2;
}
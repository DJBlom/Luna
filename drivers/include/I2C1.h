


#ifndef _I2C_1_h_ 
#define _I2C_1_h_ 
#include "I2C.h"
#include "stm32f411xe.h"
namespace Comm {
    class I2c1 : Interface::I2C {
        public:
            I2c1();
            I2c1(const I2c1&) = default;
            I2c1(I2c1&&) = default;
            I2c1& operator= (const I2c1&) = default;
            I2c1& operator= (I2c1&&) = default;
            ~I2c1() = default;

            virtual bool Write(std::uint8_t slaveAddress, std::uint8_t deviceRegister, std::uint8_t data, std::uint16_t len) override;
            virtual std::uint8_t* Read(std::uint8_t slaveAddress, std::uint8_t registerAddress, std::uint8_t data, std::uint16_t len) override;

        protected:
            virtual bool DmaWrite(std::uint8_t data, std::uint32_t len);
            virtual bool DmaRead(std::uint8_t* data, std::uint32_t len);
            virtual void I2C1Initialize();
            virtual void Dma1Initialize();
            virtual void GpioInitialize();
    };
}
#endif

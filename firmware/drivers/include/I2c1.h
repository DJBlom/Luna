


#ifndef _I2C_1_h_ 
#define _I2C_1_h_ 
#include "I2c.h"
#include "stm32f411xe.h"
static constexpr std::uint16_t I2CBUFFERSIZE{256};
namespace Comm {
    class I2c1 : public Interface::I2c {
        public:
            I2c1();
            I2c1(const I2c1&) = default;
            I2c1(I2c1&&) = default;
            I2c1& operator= (const I2c1&) = default;
            I2c1& operator= (I2c1&&) = default;
            ~I2c1() = default;

            virtual bool LineIsBusy();
            virtual void StartCommunication();
            virtual void AddressTransmission(std::uint8_t address);
            virtual void RegisterTransmission(std::uint8_t address);
            virtual bool WriteDMA(std::int8_t data, std::uint8_t len);
            virtual std::int8_t* ReadDMA(std::int8_t len);
            virtual void DisableAcknowledgement();

        protected:
            virtual bool LengthInBounds(std::int8_t len);
            virtual void I2C1Initialize();
            virtual void Dma1Initialize();
            virtual void GpioInitialize();


        private:
            enum Config: std::int8_t {
                gpioAlt = 1,
                ccr = (80 << 0),
                trise = 17,
                singleByte = 0,
            };

            enum Bounds: std::int8_t {
                upperBound = 127,
                lowerBound = 0
            };
    };
}
#endif



#ifndef _I2C_h_ 
#define _I2C_h_ 
#include <cstdint>
namespace Interface {
    class I2C {
        public:
            virtual ~I2C() = default;

            virtual bool Write(std::uint8_t slaveAddress, std::uint8_t deviceRegister, std::uint8_t data, std::uint16_t len) = 0;
            virtual std::uint8_t* Read(std::uint8_t slaveAddress, std::uint8_t registerAddress, std::uint8_t data, std::uint16_t len) = 0;
    };
}
#endif

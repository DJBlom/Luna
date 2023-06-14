

#ifndef _I2C_h_ 
#define _I2C_h_ 
#include <cstdint>
namespace Interface {
    class I2c {
        public:
            virtual ~I2c() = default;
            virtual bool LineIsBusy() = 0;
            virtual void StartCommunication() = 0;
            virtual void AddressTransmission(std::uint8_t address) = 0;
            virtual void RegisterTransmission(std::uint8_t address) = 0;
            virtual bool WriteDMA(std::int8_t data, std::uint8_t len) = 0;
            virtual std::int8_t* ReadDMA(std::int8_t len) = 0;
            virtual void DisableAcknowledgement() = 0;
    };
}
#endif

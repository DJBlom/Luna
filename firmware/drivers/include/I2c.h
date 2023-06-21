/********************************************************************************
 * Contents: I2c1 interface
 * Author: Dawid Blom
 * Date: June 21, 2023
 *
 * Note: This file defines the interface class I2c that is used as the 
 * interface from which all I2c classes will inherit.
 *******************************************************************************/
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
            virtual bool WriteI2c(std::int8_t data) = 0;
            virtual std::int8_t* ReadDMA(std::int8_t len) = 0;
            virtual void DisableAcknowledgement() = 0;
    };
}
#endif

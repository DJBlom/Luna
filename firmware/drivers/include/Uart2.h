/********************************************************************************
 * Contents: Uart2 class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file defines the class Uart2 that inherits from the interface
 * class Uart. Furthermore, it's a self contained class which means everything
 * it needs is declared and managed within it.
 *******************************************************************************/
#ifndef _UART_2_H_ 
#define _UART_2_H_ 
#include "Uart.h"
#include <cstring>
#include "stm32f411xe.h"
namespace Comm {
    class Uart2: public Interface::Uart {
        public:
            Uart2();
            Uart2(const Uart2&) = default;
            Uart2(Uart2&&) = default;
            Uart2& operator= (const Uart2&) = default;
            Uart2& operator= (Uart2&&) = default;
            virtual ~Uart2() = default;

            virtual bool Transmit(const char* data) override;

        protected:
            virtual bool TransmissionIsComplete();
            virtual bool LoadData(const char* data);
            virtual bool DataIsInBounds(const char* data);
            virtual void Uart2Initialize();
            virtual void Dma1Initialize();
            virtual void GpioInitialize();

        private:
            std::uint16_t dataLength;
            enum Config: std::uint32_t {
                gpioAlt = 0,
                baudrate = 0x113,
            };

            enum Bounds: std::uint32_t {
                upperBound = 65535,
                lowerBound = 0
            };
    };
}
#endif

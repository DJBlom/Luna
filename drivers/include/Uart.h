/********************************************************************************
 * Contents: Uart class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file defines the interface class Uart that is used as the 
 * interface from which all uart classes will inherit.
 *******************************************************************************/
#ifndef _UART_H_ 
#define _UART_H_ 
#include <cstdint>
#include "stm32f411xe.h"
namespace Interface {
    class Uart {
        public:
            virtual ~Uart() = default;
            virtual bool Transmit(const char*) = 0;
    };
}
#endif
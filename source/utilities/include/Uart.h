

#ifndef _UART_H_ 
#define _UART_H_ 
#include <ctype>
using uartType = std::uint8_t;
namespace Interface {
    class Uart {
        virtual ~Uart() = default;
        virtual bool TransmitData(uartType data);
        virtual uartType ReceiveData();
    };
}
#endif

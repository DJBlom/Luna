

#ifndef _UART2_MOCK_H_ 
#define _UART2_MOCK_H_ 
#include "Uart.h"

namespace Mock {
    class Uart2: public Interface::Uart {
        public:
            Uart2() = default;
            Uart2(const Uart2&) = default;
            Uart2(Uart2&&) = default;
            Uart2& operator= (const Uart2&) = default;
            Uart2& operator= (Uart2&&) = default;
            virtual ~Uart2() = default;

            virtual bool Transmit(const char* data);
            virtual const char* GetMessage();
    };
}
#endif 

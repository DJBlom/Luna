/*************************************************************************
 * Contents: Logger class
 * Author: Dawid Blom
 * Date: April 9, 2023
 *
 * ABOUT: This class provides an interface to log messsage to some host
 * using the UART communication protocol. Furthermore, it uses a baud 
 * rate of 115200 to log the messages. 
 ************************************************************************/
#ifndef _LOGGER_H_ 
#define _LOGGER_H_ 
#include <cstdbool>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <cstdint>
#include "stm32f411xe.h"

constexpr std::uint16_t BUFFERSIZE{256};
using loggerType = std::uint32_t;
namespace System {
    class Logger {
        public:
            Logger();
            Logger(const char* messagePrefix);
            Logger(const Logger&) = default;
            Logger(Logger&&) = default;
            Logger& operator= (const Logger&) = default;
            Logger& operator= (Logger&&) = default;
            virtual ~Logger() = default;
            virtual bool LogMessage(const char* userMessage, ...);

        protected:
            virtual void LoggerSetup(const char* messagePrefix);
            virtual void GpioConfigure();
            virtual void UartConfigure();
            virtual void DmaConfigure();
            virtual bool TransferIsComplete();

        private:
            const char* prefix{nullptr};
            char message[BUFFERSIZE];
            char buffer[BUFFERSIZE];

            enum UART2: std::uint32_t {
                GPIO_ALT = 0,
                BAUDRATE = 0x113,
            };
    };
}
#endif

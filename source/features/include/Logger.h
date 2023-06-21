/********************************************************************************
 * Contents: Logger class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This class is used to log information to a host machine using a uart.
 *******************************************************************************/
#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include "Uart.h"
static constexpr std::uint16_t LOGGERBUFFERSIZE{256};
namespace System {
    class Logger {
        public:
            Logger() = default;
            explicit Logger(const char* prefix): messagePrefix{prefix} {}
            Logger(const Logger&) = default;
            Logger(Logger&&) = default;
            Logger& operator= (const Logger&) = default;
            Logger& operator= (Logger&&) = default;
            virtual ~Logger() = default;
            virtual bool LogMessage(Interface::Uart &uart, const char* message, ...);

        protected:
            virtual bool MessageNotOutOfBounds(const char* message);
            virtual bool FormatMessage(const char* message, std::va_list vlist);

        private:
            const char* messagePrefix{"Default: "};
            char finalMessage[LOGGERBUFFERSIZE]{0};
            enum LOGGER {
                ERROR = -1,
                LOWERBOUND = 0,
                UPPERBOUND = LOGGERBUFFERSIZE
            };
    };
}
#endif

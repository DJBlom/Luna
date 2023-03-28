

#ifndef _LOGGER_H_
#define _LOGGER_H 
#include "stm32f4xx_hal.h"
namespace System {
    class Logger {
        public:
            Logger() = default;
            Logger(const char* prefixMessage);
            Logger(const Logger&) = default;
            Logger& operator= (Logger&&) = default;
            Logger& operator= (const Logger&) = default;
            virtual ~Logger() = default;

            virtual bool EnableUart2();


        private:
            const char* prefix{nullptr};
    };
}
#endif 

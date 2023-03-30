

#ifndef _LOGGER_H_
#define _LOGGER_H_ 
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

            virtual void LogMessage(const char* message);
        private:
            const char* prefix{nullptr};
    };
}
#endif 

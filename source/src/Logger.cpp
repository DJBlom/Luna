#include "Logger.h"


System::Logger::Logger(const char* prefixMessage) 
{
    this->prefix = prefixMessage;
}


bool System::Logger::EnableUart2()
{
    return true;
}

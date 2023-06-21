/********************************************************************************
 * Contents: Logger class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file implements all the methods defined in the Logger class.
 *******************************************************************************/
#include "Logger.h"


bool System::Logger::LogMessage(Interface::Uart &uart, const char* message, ...)
{
    bool isLogged{false};
    if (MessageNotOutOfBounds(message))
    {
        std::va_list listOfArguments;
        va_start(listOfArguments, message);
        if (FormatMessage(message, listOfArguments))
        {
            va_end(listOfArguments);
            isLogged = uart.Transmit(this->finalMessage);
        }
    }

    return isLogged;
}


bool System::Logger::MessageNotOutOfBounds(const char* message)
{
    bool inBounds{true};
    long unsigned int messageLength = std::strlen(message);
    if (messageLength > LOGGER::UPPERBOUND)
    {
        inBounds = false;
    }
    else if (messageLength <= LOGGER::LOWERBOUND)
    {
        inBounds = false;
    }

    return inBounds;
}


bool System::Logger::FormatMessage(const char* message, std::va_list vlist)
{
    bool formatted{false};
    char messageFormat[LOGGERBUFFERSIZE]{0};
    std::strncpy(messageFormat, this->messagePrefix, LOGGERBUFFERSIZE - 1);
    std::strncat(messageFormat, message, LOGGERBUFFERSIZE - 1);
    if (std::vsnprintf(this->finalMessage, LOGGERBUFFERSIZE, messageFormat, vlist) != LOGGER::ERROR)
    {
        formatted = true;
    }

    return formatted;
}

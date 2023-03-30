/********************************************************************************
 * Contents: Tests for the system logger.
 * Author: Dawid Blom.
 * Date: March 28, 2023.
 *
 * Note: 
 *******************************************************************************/
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Logger.h"
#include "LoggerMock.h"


extern "C" 
{

}

using genericType = std::uint32_t;

/***************** TEST LIST ***************************************************
 * 1) Initialize the system logger with a prefix message
 * 2) Enable the Uart2 for transferring data using DMA
 * 3) A method to log messages to the console.
 * 4) Enable DMA.
 **/
TEST_GROUP(SystemLoggerTest)
{

    void setup()
    {

    }

    void teardown()
    {
        mock().clear();
    }
};

TEST(SystemLoggerTest, InitializeTheSystemLoggerWithAPrefixMessage)
{
    mock().expectOneCall("DmaEnable");
    System::Logger* logger = new Mock::Logger{"System Running."};
    logger->DmaEnable();

    mock().checkExpectations();
    delete logger;
}

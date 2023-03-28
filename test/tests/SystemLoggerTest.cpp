/********************************************************************************
 * Contents: Tests for the system logger.
 * Author: Dawid Blom.
 * Date: March 28, 2023.
 *
 * Note: 
 *******************************************************************************/
#include "CppUTest/TestHarness.h"

#include "Logger.h"


extern "C" 
{

}

using genericType = std::uint32_t;

/***************** TEST LIST ***************************************************
 * 1) Initialize the system logger with a prefix message
 * 2) Enable the Uart2 for transferring data using DMA
 * 3) A method to log messages to the console.
 **/
TEST_GROUP(SystemLoggerTest)
{
    System::Logger logger;
    void setup()
    {
        logger = System::Logger{"System Running."};
    }

    void teardown()
    {
    }
};

TEST(SystemLoggerTest, EnableTheUart2ForTransferringDataUsingDMA)
{
    bool expected = true;
    bool uart2Enabled = logger.EnableUart2();

    CHECK_EQUAL(expected, uart2Enabled);
}

/********************************************************************************
 * Contents: Logger Unit Tests
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: Refer to the TEST LIST for details on what this fixture tests.
 *******************************************************************************/
extern "C" 
{

}
#include "Logger.h"
#include "Uart2Mock.h"

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"



using genericType = std::uint32_t;

/***************** TEST LIST ***************************************************
 * 1) Log messages with an unlimited amount of arguments and a default prefix. (Done)
 * 2) Log messages with an unlimited amount of arguments. (Done)
 * 3) Upper bound message limit check. Upper bound = 256 bytes. (Done)
 * 4) Lower bound message limit check. Lower bound = 0 bytes. (Done)
 * 5) Enssure the message is correctly formatted. (Done)
 **/
TEST_GROUP(LoggerTest)
{
    Mock::Uart2 uart2Mock;
    System::Logger log;
    void setup()
    {
        log = System::Logger{"System: "};
    }

    void teardown()
    {
        mock().clear();
    }
};

TEST(LoggerTest, LogMessagesWithAnUnlimitedAmountOfArgumentsAndDefaultPrefix)
{
    System::Logger logDefault;
    const char* expected = "Default: 50 percent good, ;b.\n\r";
    mock().expectOneCall("Transmit").withParameter("data", expected).andReturnValue(true);
    logDefault.LogMessage(uart2Mock, "%d percent %s, ;%c.\n\r", 50, "good", 'b');

    
    STRCMP_EQUAL(expected, uart2Mock.GetMessage());
    mock().checkExpectations();
}

TEST(LoggerTest, LogMessagesWithAnUnlimitedAmountOfArguments)
{
    const char* expected = "System: 50 percent good, ;b.\n\r";
    mock().expectOneCall("Transmit").withParameter("data", expected).andReturnValue(true);
    log.LogMessage(uart2Mock, "%d percent %s, ;%c.\n\r", 50, "good", 'b');

    STRCMP_EQUAL(expected, uart2Mock.GetMessage());
    mock().checkExpectations();
}

TEST(LoggerTest, UpperBoundOf256BytesShouldNotBeExceeded)
{
    bool expected = false;
    bool actual = log.LogMessage(uart2Mock,"kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
                                           "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
                                           "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
                                           "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"
                                           "kkkkkkkkkkkkkkkkkkkkkkkkk");

    CHECK_EQUAL(expected, actual);
}

TEST(LoggerTest, LowerBoundOf0BytesShouldNotBeExceeded)
{
    bool expected = false;
    bool actual = log.LogMessage(uart2Mock, "");

    CHECK_EQUAL(expected, actual);
}

TEST(LoggerTest, EnsureMessageFormattingIsCorrect)
{
    bool expected = false;
    bool actual = log.LogMessage(uart2Mock, "Should fail %lc:", (wint_t) -1);

    CHECK_EQUAL(expected, actual);
}














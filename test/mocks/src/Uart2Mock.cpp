#include "Uart2Mock.h"
#include "CppUTestExt/MockSupport.h"



static const char* mockMessage{nullptr};
bool Mock::Uart2::Transmit(const char* data)
{
    mockMessage = data;
    return mock().actualCall("Transmit").withParameter("data", data).returnBoolValue();
}


const char* Mock::Uart2::GetMessage()
{
    return mockMessage;
}

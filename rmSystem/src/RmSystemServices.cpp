/*******************************************************************************
 * Contents: Implementation of the system service creation function and services.
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE:
 *******************************************************************************/
#include <RmSystemServices.h>


#define TRUE 1

bool CreateSystemServices(void)
{
	BaseType_t task;
    bool success = true;

	task = xTaskCreate(Service1, "Service1", STACK_SIZE, (void*) ONE, configMAX_PRIORITIES - ONE, GetServiceHandle(ZERO));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service2, "Service2", STACK_SIZE, (void*) TWO, configMAX_PRIORITIES - TWO, GetServiceHandle(ONE));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service3, "Service3", STACK_SIZE, (void*) THREE, configMAX_PRIORITIES - THREE, GetServiceHandle(TWO));
	if (task == pdFAIL)
	{
		success = false;
	}

	return success;
}



void Service1(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    System::Logger service1{"Service"};
    std::uint32_t count = (std::uint32_t)serviceNumber;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ZERO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service1.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 50, count);

			// Load

			SetServiceWatchdogBit(ZERO);
		}
	}
}



void Service2(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    System::Logger service2{"Service"};
    std::uint32_t count = (std::uint32_t)serviceNumber;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ONE), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service2.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 20, count);

			// Load

			SetServiceWatchdogBit(ONE);
		}
	}
}



void Service3(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    System::Logger service3{"Service"};
    std::uint32_t count = (std::uint32_t)serviceNumber;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(TWO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service3.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 10, count);

			// Load

			SetServiceWatchdogBit(TWO);
		}
	}
}











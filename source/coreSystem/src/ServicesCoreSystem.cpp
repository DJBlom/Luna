/*******************************************************************************
 * Contents: ServiceCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE: Implementation of the system service creation function and services.
 *******************************************************************************/
#include <ServicesCoreSystem.h>
#define TRUE 1


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
            // Watchdog
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
            // Watchdog
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
            // Watchdog
		}
	}
}











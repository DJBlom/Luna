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

	task = xTaskCreate(Service1, "Service1", STACK_SIZE, (void*) 1, tskIDLE_PRIORITY + SIX, GetServiceHandle(ZERO));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service2, "Service2", STACK_SIZE, (void*) 2, tskIDLE_PRIORITY + FIVE, GetServiceHandle(ONE));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service3, "Service3", STACK_SIZE, (void*) 3, tskIDLE_PRIORITY + FOUR, GetServiceHandle(TWO));
	if (task == pdFAIL)
	{
		success = false;
	}

//	task = xTaskCreate(Service4, "Service4", STACK_SIZE, NULL, tskIDLE_PRIORITY + THREE, GetServiceHandle(THREE));
//	if (task == pdFAIL)
//	{
//		success = false;
//	}
//
//	task = xTaskCreate(Service5, "Service5", STACK_SIZE, NULL, tskIDLE_PRIORITY + TWO, GetServiceHandle(FOUR));
//	if (task == pdFAIL)
//	{
//		success = false;
//	}
//
//	task = xTaskCreate(Service6, "Service6", STACK_SIZE, NULL, tskIDLE_PRIORITY + ONE, GetServiceHandle(FIVE));
//	if (task == pdFAIL)
//	{
//		success = false;
//	}

	return success;
}



void Service1(void* serviceNumber)
{
    System::Logger service1{"Service"};
    std::uint8_t count{0};
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ZERO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service1.LogMessage(" %d: Running @: %dHz | Serviced: %d", (int) serviceNumber, 50, count);

			// Load

			SetServiceWatchdogBit(ZERO);
		}
	}
}



void Service2(void* serviceNumber)
{
    System::Logger service2{"Service"};
    int count{0};
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ONE), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service2.LogMessage(" %d: Running @: %dHz | Serviced: %d", (int) serviceNumber, 25, count);

			// Load

			SetServiceWatchdogBit(ONE);
		}
	}
}



void Service3(void* serviceNumber)
{
    System::Logger service3{"Service"};
    int count{0};
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(TWO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service3.LogMessage(" %d: Running @: %dHz | Serviced: %d", (int) serviceNumber, 10, count);

			// Load

			SetServiceWatchdogBit(TWO);
		}
	}
}



//void Service4(void* serviceNumber)
//{
//    System::Logger service4{"Service 4: "};
//    int serviceNum = (int) serviceNumber;
//	while (TRUE)
//	{
//		if (xSemaphoreTake(GetServiceSemaphore(THREE), (TickType_t) FIVE) == pdTRUE)
//		{
//            serviceNum++;
//            service4.LogMessage("Frequency: %dHz | Number of Times Active: %d", THREE, serviceNum);
//
//			// Load
//
//			SetServiceWatchdogBit(THREE);
//		}
//	}
//}



//void Service5(void* serviceNumber)
//{
//    System::Logger service5{"Service 5: "};
//    int serviceNum = (int) serviceNumber;
//	while (TRUE)
//	{
//		if (xSemaphoreTake(GetServiceSemaphore(FOUR), (TickType_t) FIVE) == pdTRUE)
//		{
//            serviceNum++;
//            service5.LogMessage("Frequency: %dHz | Number of Times Active: %d", FOUR, serviceNum);
//
//			// Load
//
//			SetServiceWatchdogBit(FOUR);
//		}
//	}
//}
//
//
//
//void Service6(void* serviceNumber)
//{
//    System::Logger service6{"Service 6: "};
//    int serviceNum = (int) serviceNumber;
//	while (TRUE)
//	{
//		if (xSemaphoreTake(GetServiceSemaphore(FIVE), (TickType_t) FIVE) == pdTRUE)
//		{
//            serviceNum++;
//            service6.LogMessage("Frequency: %dHz | Number of Times Active: %d", FIVE, serviceNum);
//
//			// Load
//
//			SetServiceWatchdogBit(FIVE);
//		}
//	}
//}










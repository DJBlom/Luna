/*******************************************************************************
 * Contents: Implementation of the system service creation function and services.
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE:
 *******************************************************************************/
#include <CoreSystemServices.h>


#define TRUE 1

bool CreateSystemServices( void )
{
	BaseType_t task;
    bool success = true;

	task = xTaskCreate(Service1, "Service1", STACK_SIZE, NULL, tskIDLE_PRIORITY + SIX, GetServiceHandle(ZERO));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service2, "Service2", STACK_SIZE, NULL, tskIDLE_PRIORITY + FIVE, GetServiceHandle(ONE));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service3, "Service3", STACK_SIZE, NULL, tskIDLE_PRIORITY + FOUR, GetServiceHandle(TWO));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service4, "Service4", STACK_SIZE, NULL, tskIDLE_PRIORITY + THREE, GetServiceHandle(THREE));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service5, "Service5", STACK_SIZE, NULL, tskIDLE_PRIORITY + TWO, GetServiceHandle(FOUR));
	if (task == pdFAIL)
	{
		success = false;
	}

	task = xTaskCreate(Service6, "Service6", STACK_SIZE, NULL, tskIDLE_PRIORITY + ONE, GetServiceHandle(FIVE));
	if (task == pdFAIL)
	{
		success = false;
	}

	return success;
}

void Service1( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ZERO), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(ZERO);
		}
	}
}



void Service2( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ONE), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(ONE);
		}
	}
}



void Service3( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(TWO), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(TWO);
		}
	}
}



void Service4( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(THREE), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(THREE);
		}
	}
}



void Service5( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(FOUR), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(FOUR);
		}
	}
}



void Service6( void* p )
{
    int serviceNum = (int) p;
	int count = 0;
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(FIVE), (TickType_t) FIVE) == pdTRUE)
		{
            serviceNum++;
			count++;

			// Load

			SetServiceWatchdogBit(FIVE);
		}
	}
}










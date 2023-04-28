/*******************************************************************************
 * Contents: InitializeCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE: Implementation of the CoreSystemInitialized and SystemServicesCreated
 * functions used to initialize the core system and create it's services.
 *******************************************************************************/
#include "InitializeCoreSystem.h"



bool CoreSystemInitialized(void)
{
    bool success = false;
	for (uint8_t i = 0; i < NUMBER_OF_SERVICES; i++)
	{
        TaskHandle_t serviceHandle = NULL;
        SetServiceHandle(serviceHandle);

		SetServiceSemaphore(xSemaphoreCreateBinary());
		if (GetServiceSemaphore(i) == NULL)
		{
            success = false;
            break;
		}
        else 
        {
            success = true;
        }
	}

	return success;
}



bool SystemServicesCreated(void)
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







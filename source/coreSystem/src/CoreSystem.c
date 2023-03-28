/*******************************************************************************
 * Contents: Implementation of the core system initialization function.
 * Additionally, there is a FreeRTOS specific ISR at the bottom called
 * vApplicationTickHook, and is used as a sequencer.
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE: It's important to note that this ISR is native to FreeRTOS and does not
 * require a definition, only an implementation.
 *******************************************************************************/
#include "CoreSystem.h"


static TickType_t currentTickCount = 0;

bool CoreSystemInitialization(void)
{
    bool success = false;
	SetWatchdogMask(0);

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



void vApplicationTickHook( void )
{
	currentTickCount = xTaskGetTickCountFromISR();


	if ((currentTickCount % SERVICE1_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(ZERO), NULL);
	}

	if ((currentTickCount % SERVICE2_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(ONE), NULL);
	}

	if ((currentTickCount % SERVICE3_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(TWO), NULL);
	}

	if ((currentTickCount % SERVICE4_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(THREE), NULL);
	}

	if ((currentTickCount % SERVICE5_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(FOUR), NULL);
	}

	if ((currentTickCount % SERVICE6_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(FIVE), NULL);
	}
}












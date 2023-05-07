/*******************************************************************************
 * Contents: vApplicationIdleHook and vApplicationTickHook Functions
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE: It's important to note that both the vApplicationIdleHook and 
 *       vApplicationTickHook ISRs are native to FreeRTOS and does not require 
 *       a definition, only an implementation.
 *
 * IDEA:
 *      The idea is that vApplicationIdleHook performs watchdog related resets
 *      and vApplicationTickHook is used to synchronize the tasks.
 *******************************************************************************/
#include <ConfigurationCoreSystem.h>

static TickType_t currentTickCount = 0;

void vApplicationIdleHook()
{
    // Todo.
}



void vApplicationTickHook()
{
	currentTickCount = xTaskGetTickCountFromISR();

	if ((currentTickCount & SERVICE1_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(ZERO), NULL);
	}

	if ((currentTickCount & SERVICE2_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(ONE), NULL);
	}

	if ((currentTickCount & SERVICE3_HZ) == ZERO)
	{
		xSemaphoreGiveFromISR(GetServiceSemaphore(TWO), NULL);
	}
}

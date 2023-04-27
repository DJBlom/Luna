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
#include <RmSystemConfiguration.h>


void vApplicationIdleHook( void )
{
	for (uint16_t i = 0; i < NUMBER_OF_SERVICES; i++)
	{
		if (ServiceIsRunning(i) == true)
        {
        }
        else 
        {
            break;
        }
	}
}



void vApplicationTickHook( void )
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

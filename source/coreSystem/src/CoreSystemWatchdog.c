/*******************************************************************************
 * Contents: Implementation both ServiceIsRunning and SetServiceWatchdogBit.
 * Additionally, there is FreeRTOS specific ISR in at the bottom.
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE: It's important to note that FreeRTOS specific ISR, the
 * vApplicationIdleHook is native to FreeRTOS and does not require a
 * definition, only a implementation.
 *******************************************************************************/
#include <CoreSystemWatchdog.h>

static IWDG_HandleTypeDef watchdog;

bool CoreSystemWatchdogInitialize()
{
    bool success = false;
    watchdog.Instance = IWDG;
    watchdog.Init.Prescaler = IWDG_PRESCALER_4;
    watchdog.Init.Reload = 4095;
    if(HAL_IWDG_Init(&watchdog) == HAL_OK)
    {
        success = true;
    }

    return  success;
}



bool ServiceIsRunning(uint16_t bitPosition)
{
    bool isRunning = false;
	if (((*GetWatchdogMask() >> bitPosition) & 1U) == 1U)
	{
		isRunning = true;
	}

	return isRunning;
}



bool SetServiceWatchdogBit(uint16_t serviceNumber)
{
	return (*GetWatchdogMask() = *GetWatchdogMask() | (1U << serviceNumber));
}



void vApplicationIdleHook( void )
{
	for (uint16_t i = 0; i < NUMBER_OF_SERVICES; i++)
	{
		if (ServiceIsRunning(i) == true)
        {
            HAL_IWDG_Refresh(&watchdog);
        }
        else 
        {
            break;
        }
	}
    

}

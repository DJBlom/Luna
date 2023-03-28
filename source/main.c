















#include <stdbool.h>
#include "stm32f4xx_hal.h"

#include "CoreSystem.h"
#include "CoreSystemServices.h"
#include "CoreSystemWatchdog.h"










int main(void)
{
    HAL_Init();

    if (CoreSystemInitialization() == false)
    {
    }
    else
    {
        if (CoreSystemWatchdogInitialize() == false)
        {

        }
        else 
        {
            if (CreateSystemServices() == false)
            {
            }
            else
            {
                vTaskStartScheduler();
            }
        }
    }

    return 0;
}


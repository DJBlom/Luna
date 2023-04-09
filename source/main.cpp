















#include "RmSystemSequencer.h"
#include "RmSystemServices.h"

#include "Logger.h"




int main(void)
{
    // Enable RCC clocks for usart2.
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_USART2EN; 
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_DMA1EN;

    System::Logger logger{"System: "};
    logger.LogMessage("Restarted");
    if (CoreSystemInitialization() == true)
    {
        if (CreateSystemServices() == true)
        {
            vTaskStartScheduler();
        }
        else
        {
            logger.LogMessage("Service Creation FAILED");
        }
    }
    else
    {
        logger.LogMessage("Initialization FAILED");
    }

    return 0;
}


























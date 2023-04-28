/********************************************************************************
 * Contents: The main function
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: 
 *******************************************************************************/
#include "InitializeCoreSystem.h"
#include "Peripherals.h"
#include "Logger.h"
#include "Uart2.h"








int main(void)
{
    System::Peripherals peripherals;
    peripherals.Initialize();

    // Set the gpioa mode for the green user LED
    GPIOA->MODER = GPIOA->MODER | (1U << 10);



    Comm::Uart2 uart2;
    System::Logger logger{"System: "};
    logger.LogMessage(uart2, "Restarted \n\n\r");

    if (CoreSystemInitialized())
    {
        if (SystemServicesCreated())
        {
            vTaskStartScheduler();
        }
        else
        {
            logger.LogMessage(uart2, "Service Creation FAILED \n\n\r");
        }
    }
    else
    {
        logger.LogMessage(uart2, "Initialization FAILED \n\n\r");
    }

    return 0;
}


























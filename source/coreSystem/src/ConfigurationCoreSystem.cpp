/*******************************************************************************
 * Contents: ConfigurationCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 25, 2023.
 *
 * NOTE: This file contains the implementation of the setters and getters 
 * defined in the ConfigurationCoreSystem.h file. 
 * struct CoreSystemMembers is used to hold all the freeRTOS task handles and 
 * semaphores used to create the tasks and help with synchronization.
 *
 * VARIABLES:
 * static struct CoreSystemMembers coreSystemMembers: 
 *      is used to provide access to the task handles and semaphores used in 
 *      the core system.
 *
 * static uint8_t serviceHandleIndex: 
 *      is a module variable used to keep track of the of all the service handles 
 *      that are created when the system is initialized.
 *
 * static uint8_t serviceSemaphoreIndex:
 *      is similar to that of the serviceHandleIndex except it keeps track of all 
 *      the semaphores created for the system to aid in syncrhonization of the 
 *      threads.
 *******************************************************************************/
#include <ConfigurationCoreSystem.h>


struct CoreSystemMembers
{
	TaskHandle_t* serviceHandle[NUMBER_OF_SERVICES];
	SemaphoreHandle_t serviceSemaphore[NUMBER_OF_SERVICES];
};


static struct CoreSystemMembers coreSystemMembers;
static uint8_t serviceHandleIndex = 0;
static uint8_t serviceSemaphoreIndex = 0;



bool SetServiceHandle(TaskHandle_t serviceHandle)
{
	bool success = false;
	if ((*coreSystemMembers.serviceHandle[serviceHandleIndex] = serviceHandle))
	{
		serviceHandleIndex++;
		success = true;
	}

	return success;
}


TaskHandle_t* GetServiceHandle(uint8_t serviceNumber)
{
	return coreSystemMembers.serviceHandle[serviceNumber];
}


bool SetServiceSemaphore(SemaphoreHandle_t serviceSemaphore)
{
	bool success = false;
	if ((coreSystemMembers.serviceSemaphore[serviceSemaphoreIndex] = serviceSemaphore))
	{
		serviceSemaphoreIndex++;
		success = true;
	}

	return success;
}


SemaphoreHandle_t GetServiceSemaphore(uint8_t serviceNumber)
{
	return coreSystemMembers.serviceSemaphore[serviceNumber];
}



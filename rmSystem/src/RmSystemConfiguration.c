/*******************************************************************************
 * Contents: Implementation of the core systems getters and setters used to
 * relay data upon initialization.
 * Author: Dawid Blom.
 * Date: January 25, 2023.
 *
 * NOTE: CoreSystemMembers are used in all the core system files,
 * A.K.A CoreSystem, CoreSystemConfiguration, CoresystemServices, and
 * CoreSystemWatchdog.
 *******************************************************************************/
#include <RmSystemConfiguration.h>


struct CoreSystemMembers
{
	uint16_t* watchdogMask;
	TaskHandle_t* serviceHandle[NUMBER_OF_SERVICES];
	SemaphoreHandle_t serviceSemaphore[NUMBER_OF_SERVICES];
};


struct CoreSystemMembers coreSystemMembers;
static uint8_t serviceHandleIndex = 0;
static uint8_t serviceSemaphoreIndex = 0;


bool SetWatchdogMask(uint16_t value)
{
	bool success = false;
	if ((*coreSystemMembers.watchdogMask = value))
	{
		success = true;
	}

	return success;
}


uint16_t* GetWatchdogMask()
{
	return coreSystemMembers.watchdogMask;
}


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



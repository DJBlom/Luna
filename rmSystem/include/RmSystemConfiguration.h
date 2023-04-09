/*******************************************************************************
 * Contents: System configuration module that acts as data relay between the
 * core system and it's services.
 * Author: Dawid Blom.
 * Date: January 25, 2023.
 *
 * NOTE: A.K.A a bunch of setters and getters used by the core system and it's
 * services for initialization and sequencing.
 *******************************************************************************/
#ifndef _RM_SYSTEM_CONFIGURATION_H_
#define _RM_SYSTEM_CONFIGURATION_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

#include <stdint.h>
#include <stdbool.h>

#define NUMBER_OF_SERVICES 3
#define STACK_SIZE 250

enum
{
	SERVICE1_HZ = 2,  // Fifty Hz
	SERVICE2_HZ = 10, // Ten Hz
	SERVICE3_HZ = 20, // Five Hz
//	SERVICE4_HZ = 25, // Four Hz
//	SERVICE5_HZ = 50, // Two Hz
//	SERVICE6_HZ = 100 // One Hz
};

enum
{
	ZERO, ONE, TWO,
	THREE, FOUR, FIVE,
	SIX
};


bool SetWatchdogMask(uint16_t value);
uint16_t* GetWatchdogMask(void);

bool SetServiceHandle(TaskHandle_t serviceHandle);
TaskHandle_t* GetServiceHandle(uint8_t serviceNumber);

bool SetServiceSemaphore(SemaphoreHandle_t serviceSemaphore);
SemaphoreHandle_t GetServiceSemaphore(uint8_t serviceNumber);

#ifdef __cplusplus
}
#endif

#endif

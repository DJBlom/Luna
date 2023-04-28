/*******************************************************************************
 * Contents: ConfigurationCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 25, 2023.
 *
 * NOTE: This file contains the core system configuration and necessary 
 * freeRTOS data to run multiple threads. Furthermore, we can access it 
 * through controlled setters and getters provided in the module. 
 *
 * VARIABLES:
 * enum Frequency: 
 *      This enum is used to set the frequency at which the threads should be 
 *      synchronized. Whether they should run at 50 Hz, 20Hz, or 10Hz, etc.
 *
 * enum Service: 
 *      This enum is used to specify thread priority and aid in the 
 *      synchronization of the threads.
 *******************************************************************************/
#ifndef _CONFIGURATION_CORE_SYSTEM_H_
#define _CONFIGURATION_CORE_SYSTEM_H_
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
#define STACK_SIZE 500

enum Frequency
{
	SERVICE1_HZ = 0x2,  // Fifty Hz
	SERVICE2_HZ = 0x5,  // Ten Hz
	SERVICE3_HZ = 0x10, // Five Hz
};

enum Services
{
	ZERO, 
    ONE, 
    TWO,
	THREE,
    FOUR,
    FIVE,
    SIX
};


bool SetServiceHandle(TaskHandle_t serviceHandle);
TaskHandle_t* GetServiceHandle(uint8_t serviceNumber);

bool SetServiceSemaphore(SemaphoreHandle_t serviceSemaphore);
SemaphoreHandle_t GetServiceSemaphore(uint8_t serviceNumber);
#ifdef __cplusplus
}
#endif
#endif

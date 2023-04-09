/*******************************************************************************
 * Contents: Functions to check whether or not the system is still healthy and
 * help maintain the system in a healthy state.
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE:
 *******************************************************************************/
#ifndef _RM_SYSTEM_WATCHDOG_H_
#define _RM_SYSTEM_WATCHDOG_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <RmSystemConfiguration.h>
bool ServiceIsRunning(uint16_t bitPosition);
bool SetServiceWatchdogBit(uint16_t serviceNumber);
#ifdef __cplusplus
}
#endif
#endif

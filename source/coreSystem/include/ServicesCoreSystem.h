/*******************************************************************************
 * Contents: ServiceCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE: An interface to all the services used in the system.
 *******************************************************************************/
#ifndef _SERVICES_CORE_SYSTEM_H_
#define _SERVICES_CORE_SYSTEM_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "ConfigurationCoreSystem.h"
#include "Logger.h"
#include "Uart2.h"

void Service1(void* p);
void Service2(void* p);
void Service3(void* p);
#ifdef __cplusplus
}
#endif
#endif

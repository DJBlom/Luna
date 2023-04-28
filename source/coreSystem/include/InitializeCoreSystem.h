/*******************************************************************************
 * Contents: InitializeCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 15, 2023.
 *
 * NOTE: This module is used to initialize the core system with the 
 * specifications in the ConfigurationCoreSystem.h file. Additionally, it 
 * creates all the services of the system. 
 *******************************************************************************/
#ifndef _INTITIALIZE_CORE_SYSYSTEM_H_
#define _INTITIALIZE_CORE_SYSYSTEM_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "ConfigurationCoreSystem.h"
#include "ServicesCoreSystem.h"

bool CoreSystemInitialized(void);
bool SystemServicesCreated(void);
#ifdef __cplusplus
}
#endif
#endif

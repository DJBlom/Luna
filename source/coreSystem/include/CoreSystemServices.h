/*******************************************************************************
 * Contents: System service creation function and services.
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE:
 *******************************************************************************/
#ifndef _CORE_SYSTEM_SERVICES_H_
#define _CORE_SYSTEM_SERVICES_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <CoreSystemConfiguration.h>
#include <CoreSystemWatchdog.h>

bool CreateSystemServices(void);
void Service1( void* p );
void Service2( void* p );
void Service3( void* p );
void Service4( void* p );
void Service5( void* p );
void Service6( void* p );

#ifdef __cplusplus
}
#endif
#endif

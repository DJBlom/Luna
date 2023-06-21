/*******************************************************************************
 * Contents: ServiceCoreSystem Module
 * Author: Dawid Blom.
 * Date: January 20, 2023.
 *
 * NOTE: Implementation of the system service creation function and services.
 *******************************************************************************/
#include <ServicesCoreSystem.h>
#define TRUE 1







void Service1(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    System::Logger service1{"Service"};
    std::uint32_t count{0}; 
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ZERO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service1.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 50, count);

			// Load
            // Watchdog
		}
	}
}



void Service2(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    System::Logger service2{"Service"};
    std::uint32_t count{0};
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(ONE), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            service2.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 20, count);

			// Load
            // Watchdog
		}
	}
}



void Service3(void* serviceNumber)
{
    Comm::Uart2 uart2; 
    Comm::I2c1 i2c1;
    Sensor::MPU6050 mpu6050;
    mpu6050.Initialize(i2c1);
    System::Logger service3{"Service"};
    std::uint32_t count = (std::uint32_t)serviceNumber;
//    std::uint32_t count{0};
    std::int8_t* data{nullptr};
    std::int16_t x;
    std::int16_t y;
    std::int16_t z;  
	while (TRUE)
	{
		if (xSemaphoreTake(GetServiceSemaphore(TWO), (TickType_t) FIVE) == pdTRUE)
		{
            count++;
            data = mpu6050.ReadGyrometerData(i2c1);
            x = (std::int16_t)(data[0] << 8 | data[1]);
            y = (std::int16_t)(data[2] << 8 | data[3]);
            z = (std::int16_t)(data[4] << 8 | data[5]);
            service3.LogMessage(uart2, " 3: X = %d, Y = %d, Z = %d \n\n\r", (x / 131), (y / 131), (z / 131));
//            service3.LogMessage(uart2, " %d: Running @: %dHz | Serviced: %d \n\n\r", (int) serviceNumber, 10, count);

			// Load
            // Watchdog
		}
	}
}











/********************************************************************************
 * Contents: MPU6050 class
 * Author: Dawid Blom
 * Date: June 21, 2023
 *
 * Note: This file implements all the methods defined in the MPU6050 class. 
 *******************************************************************************/
#include "MPU6050.h"

bool Sensor::MPU6050::Initialize(Interface::I2c& i2c)
{
    bool isInitialized{false};
    if (*DeviceNumber(i2c) == Device::Id)
    {
        PowerInitialization(i2c);
        SampleRateInitialization(i2c);
        GyrometerInitialization(i2c);
        isInitialized = true;
    }

    return isInitialized;
}


std::int8_t* Sensor::MPU6050::ReadGyrometerData(Interface::I2c& i2c)
{
    static std::int8_t* temp{nullptr};
    if (i2c.LineIsBusy() == false)
    {
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::write);
        i2c.RegisterTransmission(Registers::xOutGyroH);
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::read);
        temp = i2c.ReadDMA(Config::sixBytes);
    }

    return temp;
}


std::int8_t* Sensor::MPU6050::DeviceNumber(Interface::I2c& i2c)
{
    static std::int8_t* temp{nullptr};
    if (i2c.LineIsBusy() == false)
    {
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::write);
        i2c.RegisterTransmission(Registers::whoAmI);
        i2c.StartCommunication();
        i2c.DisableAcknowledgement();
        i2c.AddressTransmission(Mode::read);
        temp = i2c.ReadDMA(Config::singleByte);
    }

    return temp;
}


void Sensor::MPU6050::PowerInitialization(Interface::I2c& i2c)
{
    i2c.StartCommunication();
    i2c.AddressTransmission(Mode::write);
    i2c.RegisterTransmission(Registers::power);
    i2c.WriteI2c(Config::powerConfig);
}


void Sensor::MPU6050::SampleRateInitialization(Interface::I2c& i2c)
{
    i2c.StartCommunication();
    i2c.AddressTransmission(Mode::write);
    i2c.RegisterTransmission(Registers::sampleRate);
    i2c.WriteI2c(Config::sampleRateConfig);
}


void Sensor::MPU6050::GyrometerInitialization(Interface::I2c& i2c)
{
    i2c.StartCommunication();
    i2c.AddressTransmission(Mode::write);
    i2c.RegisterTransmission(Registers::gyrometer);
    i2c.WriteI2c(Config::gyrometerConfig);
}














#include "MPU6050.h"

bool Sensor::MPU6050::Initialize(Interface::I2c& i2c)
{
    bool isInitialized{true};
    if (i2c.LineIsBusy())
    {
        isInitialized = false;
    }
    else if (*DeviceNumber(i2c) == Device::Id)
    {
        PowerInitialization(i2c);
        SampleRateInitialization(i2c);
        GyrometerInitialization(i2c);
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


bool Sensor::MPU6050::PowerInitialization(Interface::I2c& i2c)
{
    bool isInitialized{true};
    if (i2c.LineIsBusy())
    {
        isInitialized = false;
    }
    else 
    {
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::write);
        i2c.RegisterTransmission(Registers::power);
        i2c.WriteDMA(Config::powerConfig, Config::singleByte);
    }

    return isInitialized;
}


bool Sensor::MPU6050::SampleRateInitialization(Interface::I2c& i2c)
{
    bool isInitialized{true};
    if (i2c.LineIsBusy())
    {
        isInitialized = false;
    }
    else 
    {
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::write);
        i2c.RegisterTransmission(Registers::sampleRate);
        i2c.WriteDMA(Config::sampleRateConfig, Config::singleByte);
    }

    return isInitialized;
}


bool Sensor::MPU6050::GyrometerInitialization(Interface::I2c& i2c)
{
    bool isInitialized{true};
    if (i2c.LineIsBusy())
    {
        isInitialized = false;
    }
    else 
    {
        i2c.StartCommunication();
        i2c.AddressTransmission(Mode::write);
        i2c.RegisterTransmission(Registers::gyrometer);
        i2c.WriteDMA(Config::gyrometerConfig, Config::singleByte);
    }

    return isInitialized;
}











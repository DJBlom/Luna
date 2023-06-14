


#ifndef _MPU6050_h_ 
#define _MPU6050_h_ 
#include <cstdint>
#include "I2C.h"
namespace Sensor {
    class MPU6050 {
        public:
            MPU6050() = default;
            MPU6050(const MPU6050&) = default;
            MPU6050(MPU6050&&) = default;
            MPU6050& operator=(const MPU6050&) = default;
            MPU6050& operator=(MPU6050&&) = default;
            virtual ~MPU6050() = default;
            virtual bool Initialize(Interface::I2c& i2c);
            virtual std::int8_t* ReadGyrometerData(Interface::I2c& i2c);

        protected:
            virtual std::int8_t* DeviceNumber(Interface::I2c& i2c);
            virtual bool PowerInitialization(Interface::I2c& i2c);
            virtual bool SampleRateInitialization(Interface::I2c& i2c);
            virtual bool GyrometerInitialization(Interface::I2c& i2c);

        private:
            enum Device: std::int32_t {
                Id = 0x68
            };

            enum Config: std::int8_t {
                singleByte = 2,
                sixBytes = 6,
                powerConfig = 0x0,
                sampleRateConfig = 0x7,
                gyrometerConfig = 0x0
            };

            enum Mode: std::int32_t {
                write = 0xD0,
                read = write + 1,
            };

            enum Registers: std::int32_t {
                whoAmI = 0x75,
                power = 0x6B,
                sampleRate = 0x19,
                gyrometer = 0x1B,
                xOutGyroH = 0x43
            };
    };
}
#endif

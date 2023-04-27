/********************************************************************************
 * Contents: Peripherals class
 * Author: Dawid Blom
 * Date: April 13, 2023
 *
 * Note: This file defines peripheral class and all it's methods used to 
 * initialize the system with the desired peripherals activated. Additionally,
 * it a manages the all the systems interrupt routines initialization too. 
 *******************************************************************************/
#ifndef _PERIPHERALS_H_ 
#define _PERIPHERALS_H_ 
#include "stm32f411xe.h"
namespace System {
    class Peripherals {
        public:
            Peripherals() = default;
            Peripherals(const Peripherals&) = default;
            Peripherals(Peripherals&&) = default;
            Peripherals& operator= (const Peripherals&) = default;
            Peripherals& operator= (Peripherals&&) = default;
            virtual ~Peripherals() = default;

            void Initialize();

        protected:
            void RccInitialization();
            void EnableIRQHandlers();
    };
}
#endif 

#include "MCP9700.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "peripherals/ADC/ADC.h"

//Configure the ADC to measure the output of the MCP9700
void MCP9700_init(void)
{
    //Set to AIN15 (PD5)
    ADC_setSamplingChannel(5);
}

//Returns the temperature of the MCP9700 in Celsius 
uint8_t MCP9700_measureTemperature(void)
{
    //Start measurement
    ADC_startConversion();
    
    //Wait...
    while (ADC_isBusy()) { ; }
    
    //Get result, and right shift by 3 (to compensate for 8x oversampling)
    uint16_t result = (ADC_getAccumulation()) >> 3;
    
    //If the result is smaller than the device offset at 0C, it is likely a sensor failure
    if (result < MCP9700_OFFSET)
    {
        return 0xFF;
    }
    
    //At 10-bit resolution and 1.024V reference, each bit is 1 mV
    uint8_t temp_out = ceil((result - MCP9700_OFFSET) / MCP9700_TEMPCO);

    //Return Result
    return temp_out;
}

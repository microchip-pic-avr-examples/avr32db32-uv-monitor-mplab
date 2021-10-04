#include "DAC.h"

#include <xc.h>



//Initialize the DAC peripheral
void DAC_init(void)
{
    //Set DAC Voltage Reference to Internal 1.024V reference
    VREF.DAC0REF = VREF_REFSEL_1V024_gc;
        
    //Set the DAC's default value
    DAC_setValue(DAC_DEFAULT);
    
    //Enable Analog Output (does NOT enable DAC)
    DAC0.CTRLA = DAC_OUTEN_bm;
}

//Enable the DAC
void DAC_enable(void)
{
    DAC0.CTRLA |= DAC_ENABLE_bm;
}

//Turn off the DAC
void DAC_disable(void)
{
    DAC0.CTRLA &= ~DAC_ENABLE_bm;
}

//Get the 10-bit value in the DAC
uint16_t DAC_getValue(void)
{
    return (DAC0.DATAH << 8) | DAC0.DATAL;
}

//Set the 10-bit value in the DAC
void DAC_setValue(uint16_t value)
{
    DAC0.DATAL = (value & 0x03) << 6;
    DAC0.DATAH = (value >> 2);
}
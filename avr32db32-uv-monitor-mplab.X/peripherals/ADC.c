#include "ADC.h"

#include <xc.h>

void ADC_init(void)
{
    //Select 1.024V for ADC Reference
    VREF.ADC0REF = VREF_REFSEL_1V024_gc;
    
    //Enable Operation in Debug
    ADC0.DBGCTRL = ADC_DBGRUN_bm;
    
    //Accumulate 8 samples
    ADC0.CTRLB = ADC_SAMPNUM_ACC8_gc;
    
    //Number of Clock Cycles + 2 to acquire for
    ADC0.SAMPCTRL = 255; //0x01;
    
    //10-bit Resolution, ADC Enabled
    ADC0.CTRLA = ADC_RESSEL_10BIT_gc | ADC_ENABLE_bm;
}

//Sets the sampling channel of the ADC
void ADC_setSamplingChannel(uint8_t channel)
{
    ADC0.MUXPOS = channel;
    ADC0.MUXNEG = ADC_MUXNEG_GND_gc;
}

//Starts an ADC Conversion
void ADC_startConversion(void)
{
    ADC0.COMMAND = ADC_STCONV_bm;
}

//Returns true if the ADC is converting
bool ADC_isBusy(void)
{
    return (ADC0.COMMAND & ADC_STCONV_bm);
}

//Read the result accumulation register of the ADC
uint16_t ADC_getAccumulation(void)
{
    return ADC0.RES;
}

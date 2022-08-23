#include "switcher.h"
#include "peripherals/TCD.h"
#include "peripherals/AC.h"
#include "peripherals/CCL.h"
#include "peripherals/EVSYS.h"
#include "peripherals/TCB.h"
#include "peripherals/ADC.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//Min and Max Duty Cycle Counts (not percent)
#define MIN_DUTY_CYCLE 1
#define DEFAULT_DUTY_CYCLE 10
#define MAX_DUTY_CYCLE 20

//Protective timeout
#define TIMEOUT_LIMIT 20

//Threshold for Reducing Boost Converter Duty Cycle
const uint16_t DC_REDUCE_THRESHOLD = PULSE_WAIT * 0.90;

void SWITCHER_initBoost(void)
{   
    //Select PD3 for Sampling
    ADC_setSamplingChannel(ADC_MUXPOS_AIN3_gc);
    
    //Start ADC 
    ADC_startConversion();
    
    //Wait...
    while (ADC_isBusy());
    
    //Get Result
    if (ADC_getAccumulation() < SWITCHER_SAFETY_MIN)
    {
        //Network appears broken!
        return;
    }
    
    //Set # of pulses to measure
    TCB_setPulseTimeout(PULSE_WAIT);
    
    //Set the Default Duty Cycle
    TCD_setCMPCLRA(DEFAULT_DUTY_CYCLE);
    
    //Start TCD
    TCD_start();
}
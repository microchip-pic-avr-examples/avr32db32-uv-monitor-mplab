#include "switcher.h"
#include "peripherals/TCD.h"
#include "peripherals/AC.h"
#include "peripherals/CCL.h"
#include "peripherals/EVSYS.h"
#include "peripherals/TCB.h"

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
    //Set # of pulses to measure
    TCB_setPulseTimeout(PULSE_WAIT);
    
    //Set the Default Duty Cycle
    TCD_setCMPCLRA(DEFAULT_DUTY_CYCLE);
    
    //Start TCD
    TCD_start();
}

void SWITCHER_adjustPowerOutputBlocking(void)
{
    //If # of TCD Pulses = # of Output Pulses, increase duty cycle
    //If # of TCD Pulses < DC_REDUCE_THRESHOLD, decrease duty cycle
    
    uint16_t pulseCount;
    uint16_t missed = 0;
    
    uint8_t timeout = 0;
    
    do
    {
        //Start Missed Pulse Counter
        TCB_startOneShotCounters();

        //Wait...
        TCB_waitForPulses();

        //Stop Counter
        TCB_stopOutputCounter();

        /* 
         * In a VERY rare event, it might be possible for TCB0 to have
         * double counted pulses (caused by a 2nd rising edge in the 
         * middle of a cycle). 
         * 
         * To prevent against this, if TCB0 > PULSE_WAIT, then missed = 0
         */
        
        //Get the counted pulse
        pulseCount = TCB_getOutputPulses();

        if (pulseCount < PULSE_WAIT)
        {
            missed = PULSE_WAIT - TCB_getOutputPulses();
        }

        if (missed == 0)
        {
            //Adjust DC up

            if (TCD_getDutyCycle() < MAX_DUTY_CYCLE)
            {
                //Not at max value
                TCD_incrementDutyCycle();
                
            }
        }
        else if (DC_REDUCE_THRESHOLD >= pulseCount)
        {
            //Adjust DC down

            if (TCD_getDutyCycle() > MIN_DUTY_CYCLE)
            {
                //Not at min value
                TCD_decrementDutyCycle();
            }
        }
        else
        {
            //Everything is good
            
            return;
        }
        
        //Sync Changes
        TCD0.CTRLE = TCD_SYNC_bm;
        
        //Increment Timeout
        timeout++;
        
    } while(timeout < TIMEOUT_LIMIT);
    
}

void SWITCHER_adjustPowerOutputISR(void)
{
    //If # of TCD Pulses = # of Output Pulses, increase duty cycle
    //If # of TCD Pulses < DC_REDUCE_THRESHOLD, decrease duty cycle
    
    uint16_t pulseCount;
    uint16_t missed = 0;
    
    //Start Missed Pulse Counter
    TCB_startOneShotCounters();

    //Wait...
    TCB_waitForPulses();

    //Stop Counter
    TCB_stopOutputCounter();

    /* 
     * In a VERY rare event, it might be possible for TCB0 to have
     * double counted pulses (caused by a 2nd rising edge in the 
     * middle of a cycle). 
     * 
     * To prevent against this, if TCB0 > PULSE_WAIT, then missed = 0
     */

    //Get the counted pulse
    pulseCount = TCB_getOutputPulses();

    if (pulseCount < PULSE_WAIT)
    {
        missed = PULSE_WAIT - TCB_getOutputPulses();
    }

    if (missed == 0)
    {
        //Adjust DC up

        if (TCD_getDutyCycle() < MAX_DUTY_CYCLE)
        {
            //Not at max value
            TCD_incrementDutyCycle();

        }
    }
    else if (DC_REDUCE_THRESHOLD >= pulseCount)
    {
        //Adjust DC down

        if (TCD_getDutyCycle() > MIN_DUTY_CYCLE)
        {
            //Not at min value
            TCD_decrementDutyCycle();
        }
    }
    else
    {
        //Everything is good

        return;
    }

    //Sync Changes
    TCD0.CTRLE = TCD_SYNC_bm;
}
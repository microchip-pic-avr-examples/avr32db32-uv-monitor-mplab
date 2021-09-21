#include "switcher.h"
#include "peripherals/TCD/TCD.h"
#include "peripherals/AC/AC.h"
#include "peripherals/CCL/CCL.h"
#include "peripherals/EVSYS/EVSYS.h"
#include "peripherals/TCB/TCB.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//Min and Max Duty Cycle Counts
#define MIN_DUTY_CYCLE 1
#define DEFAULT_DUTY_CYCLE 10
#define MAX_DUTY_CYCLE 20

//Protective timeout
#define TIMEOUT_LIMIT 20

//Threshold for Reducing Boost Converter Duty Cycle
const uint16_t DC_REDUCE_THRESHOLD = PULSE_WAIT * 0.90;

void initBoost(void)
{
    //Init TCD
    initTCD();
    
    //Init CCL
    initCCL();
    
    //Init AC
    initAC();
    
    //Init the Event System
    initEVSYS();
    
    //Init TCB
    initTCB();
    
    //Set # of pulses to measure
    setPulseTimeoutTCB1(PULSE_WAIT);
    
    //Set the Default Duty Cycle
    setCMPCLRA(DEFAULT_DUTY_CYCLE);
    
    //Start TCD
    startTCD();
}

void adjustPowerOutputBlocking(void)
{
    //If # of TCD Pulses = # of Output Pulses, increase duty cycle
    //If # of TCD Pulses < DC_REDUCE_THRESHOLD, decrease duty cycle
    
    uint16_t pulseCount;
    uint16_t missed = 0;
    
    uint8_t timeout = 0;
    
    do
    {
        //Start Missed Pulse Counter
        startOneShotCounters();

        //Wait...
        waitForPulses();

        //Stop Counter
        stopOutputCounter();

        /* 
         * In a VERY rare event, it might be possible for TCB0 to have
         * double counted pulses (caused by a 2nd rising edge in the 
         * middle of a cycle). 
         * 
         * To prevent against this, if TCB0 > PULSE_WAIT, then missed = 0
         */
        
        //Get the counted pulse
        pulseCount = getPulseCountTCB0();

        if (pulseCount < PULSE_WAIT)
        {
            missed = PULSE_WAIT - getPulseCountTCB0();
        }

        if (missed == 0)
        {
            //Adjust DC up

            if (getDutyCycle() < MAX_DUTY_CYCLE)
            {
                //Not at max value
                incrementDutyCycle();
                
            }
        }
        else if (DC_REDUCE_THRESHOLD >= pulseCount)
        {
            //Adjust DC down

            if (getDutyCycle() > MIN_DUTY_CYCLE)
            {
                //Not at min value
                decrementDutyCycle();
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

void _adjustPowerOutputISR(void)
{
    //If # of TCD Pulses = # of Output Pulses, increase duty cycle
    //If # of TCD Pulses < DC_REDUCE_THRESHOLD, decrease duty cycle
    
    uint16_t pulseCount;
    uint16_t missed = 0;
    
    //Start Missed Pulse Counter
    startOneShotCounters();

    //Wait...
    waitForPulses();

    //Stop Counter
    stopOutputCounter();

    /* 
     * In a VERY rare event, it might be possible for TCB0 to have
     * double counted pulses (caused by a 2nd rising edge in the 
     * middle of a cycle). 
     * 
     * To prevent against this, if TCB0 > PULSE_WAIT, then missed = 0
     */

    //Get the counted pulse
    pulseCount = getPulseCountTCB0();

    if (pulseCount < PULSE_WAIT)
    {
        missed = PULSE_WAIT - getPulseCountTCB0();
    }

    if (missed == 0)
    {
        //Adjust DC up

        if (getDutyCycle() < MAX_DUTY_CYCLE)
        {
            //Not at max value
            incrementDutyCycle();

        }
    }
    else if (DC_REDUCE_THRESHOLD >= pulseCount)
    {
        //Adjust DC down

        if (getDutyCycle() > MIN_DUTY_CYCLE)
        {
            //Not at min value
            decrementDutyCycle();
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
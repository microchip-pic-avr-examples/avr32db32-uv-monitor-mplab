#include "../utility.h"

#include <xc.h>

void _initTCB0(void)
{
    //Run in standby, clock source is event system
    TCB0.CTRLA = TCB_CLKSEL_EVENT_gc;
    
    //Single-Shot
    TCB0.CTRLB = TCB_CNTMODE_SINGLE_gc;
    
    //Enable run in debug
    TCB0.DBGCTRL = TCB_DBGRUN_bm;
    
    //Max Compare Value
    TCB0.CCMP = 0xFFFF;
}

void _initTCB1(void)
{
    //Run in standby, clock source is event system
    TCB1.CTRLA = TCB_CLKSEL_EVENT_gc;
    
    //Single-Shot
    TCB1.CTRLB = TCB_CNTMODE_SINGLE_gc;
    
    //Enable run in debug
    TCB1.DBGCTRL = TCB_DBGRUN_bm;
    
    //Set timeout to a default value
    TCB1.CCMP = 100;

}

void _initTCB2(void)
{
    //Run in standby, clock source is event system (RTC 1kHz)
    TCB2.CTRLA = TCB_CLKSEL_EVENT_gc;
    
    //Single-Shot
    TCB2.CTRLB = TCB_CNTMODE_SINGLE_gc;
    
    //Enable run in debug
    TCB2.DBGCTRL = TCB_DBGRUN_bm;
    
    //Set timeout to a default value
    TCB2.CCMP = 1000;
}

void TCB_init(void)
{
    _initTCB0();
    _initTCB1();
    _initTCB2();
}

//Start TCB0 and TCB1
void TCB_startOneShotCounters(void)
{
    //Clear Counters
    TCB0.CNT = 0;
    TCB1.CNT = 0;
    
    //Start Counters
    TCB0.CTRLA |= TCB_ENABLE_bm;
    TCB1.CTRLA |= TCB_ENABLE_bm;
}

void TCB_setPulseTimeout(uint16_t count)
{
    TCB1.CCMP = count;
}

//Get the number of output pulses
uint16_t TCB_getOutputPulses(void)
{
    return TCB0.CNT;
}

//Halt Output Pulse Counter
void TCB_stopOutputCounter(void)
{
    TCB0.CTRLA &= ~TCB_ENABLE_bm;
}

//Wait for TCB1 to finish
void TCB_waitForPulses(void)
{
    while (TCB1.STATUS);
}


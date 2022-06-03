#include "TCA0.h"

#include <avr/io.h>

//Init the TCA Peripheral
void TCA0_init(void)
{
    //PF1 Output
    
    //Enable in Debug Mode
    TCA0.SINGLE.DBGCTRL = TCA_SINGLE_DBGRUN_bm;
    
    //Enable CMP1 Output (WO1 - PF1), SINGLE-SLOPE PWM
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    
    //Set Period (100 Hz)
    TCA0.SINGLE.PER = 38;
    
    //Set Duty Cycle for CMP1
    TCA0.SINGLE.CMP1 = 30;
    
    //Fper / 1024
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc;
}

//Start TCA
void TCA0_start(void)
{
    //Enable
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

//Stop TCA
void TCA0_stop(void)
{
    //Disable the timer
    TCA0.SINGLE.CTRLA &= ~(TCA_SINGLE_ENABLE_bm);
    
    //Set output to 0 to prevent current leakage when disabled
    //(Note: Inverted IO)
    TCA0.SINGLE.CTRLC &= ~(TCA_SINGLE_CMP1OV_bm);
}

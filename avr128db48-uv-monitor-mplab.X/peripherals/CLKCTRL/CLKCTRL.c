#include "CLKCTRL.h"
#include "../utility.h"

#include <xc.h>

void initClocks(void)
{
    //System Clock is OSCHF
    UNLOCK_CCP();
    CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSCHF_gc;
    
    //Set HF Oscillator to 4 MHz
    UNLOCK_CCP();
    CLKCTRL.OSCHFCTRLA = CLKCTRL_FRQSEL_4M_gc;
    
    //Enable CLK_MAIN prescaler at 4x
    //UNLOCK_CCP();
    //CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_4X_gc | CLKCTRL_PEN_bm;
}

void setOsc4M(void)
{
    
}
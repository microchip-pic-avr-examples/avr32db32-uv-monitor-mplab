#include "CLKCTRL.h"
#include "../utility.h"

#include <xc.h>

void CLKCTRL_init(void)
{    
    //Set HF Oscillator to 4 MHz
    _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FRQSEL_4M_gc); 
    
    //Enable CLKOUT
    //_PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, CLKCTRL_CLKOUT_bm); 
}

void CLKCTRL_setOsc4M(void)
{
    
}
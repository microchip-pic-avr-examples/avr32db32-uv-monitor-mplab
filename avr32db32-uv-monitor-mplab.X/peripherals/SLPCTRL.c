#include "SLPCTRL.h"

#include <avr/io.h>

void SLPCTRL_init(void)
{
    //Enable PDOWN Sleep
    SLPCTRL.CTRLA = SLPCTRL_SMODE_PDOWN_gc | SLPCTRL_SEN_bm;
    
    //Enable High-Temp Leakage Reduction
    //WARNING: See Datasheet for Limitations!
    _PROTECTED_WRITE(SLPCTRL.VREGCTRL, SLPCTRL_HTLLEN_bm);
}
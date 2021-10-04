#include "CCL.h"

#include <xc.h>

void configureCCLPins(void)
{
    //Use Alt. Pin Location (PA6) for LUT0 Out
    
    PORTMUX.CCLROUTEA = PORTMUX_LUT0_ALT1_gc;
}

void CCL_init(void)
{
    //Logic Function: TCD0 (PWM) & AC
    //Inputs: TCD0, AC1
    
    //Setup I/O
    configureCCLPins();
    
    //Select AC1 and TCD0 Inputs
    CCL.LUT0CTRLB  = CCL_INSEL1_AC1_gc | CCL_INSEL0_TCD0_gc;
    
    //0x04 - Only Active if TCD & AC
    CCL.TRUTH0 = CCL_TRUTH3_bm;
    
    //Enable Output to Pin, Select OSCHF for clocking, Enable LUT0
    CCL.LUT0CTRLA = CCL_OUTEN_bm | CCL_CLKSRC_OSCHF_gc | CCL_ENABLE_bm;
    
    //Allow Run in Standby and Enable the Peripheral
    CCL.CTRLA = CCL_RUNSTDBY_bm | CCL_ENABLE_bm;
}
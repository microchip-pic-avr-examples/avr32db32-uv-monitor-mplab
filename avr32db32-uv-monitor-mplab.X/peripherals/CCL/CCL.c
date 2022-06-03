#include "CCL.h"

#include <xc.h>

void CCL_init(void)
{
    //Logic Function: TCD0 (PWM) & AC
    //Inputs: TCD0, AC1
        
    //Select AC1 and TCD0 Inputs
    CCL.LUT0CTRLB  = CCL_INSEL1_AC1_gc | CCL_INSEL0_TCD0_gc;
    
    //0x04 - Only Active if TCD & AC
    CCL.TRUTH0 = CCL_TRUTH_3_bm;
    
    //Select OSCHF for clocking, Enable LUT0
    CCL.LUT0CTRLA = CCL_CLKSRC_OSCHF_gc | CCL_ENABLE_bm;
    
    //Allow Run in Standby and Enable the Peripheral
    CCL.CTRLA = CCL_ENABLE_bm;
}
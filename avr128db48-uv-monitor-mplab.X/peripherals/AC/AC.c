#include "AC.h"

#include <xc.h>

void AC_init(void)
{
    //Select DACREF Source (1.024V)
    VREF.ACREF = VREF_REFSEL_1V024_gc;
    
    //Inverted Output, Initial Value Low, AINP1 (PD3), DACREF
    AC1.MUXCTRL = AC_INVERT_bm | AC_INITVAL_LOW_gc | AC_MUXPOS_AINP1_gc | AC_MUXNEG_DACREF_gc;
    
    //Divider Ratio 1:11
    //Set DACREF at ~450mV
    AC1.DACREF = 113;
    
    //Slow response, med. hysteresis, Enable
    AC1.CTRLA = AC_POWER_PROFILE2_gc | AC_HYSMODE_MEDIUM_gc | AC_ENABLE_bm;
}
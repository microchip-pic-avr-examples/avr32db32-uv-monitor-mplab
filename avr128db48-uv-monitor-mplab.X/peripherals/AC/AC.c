#include "AC.h"

#include <xc.h>

void configureACPins(void)
{
    //Set as analog input (PD3)
    PORTD.DIRCLR = PIN3_bm;
    
    //Disable Digital Input Buffer
    PORTD.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
    
    //Enable Output Buffer (PA7)
    PORTA.DIRSET = PIN7_bm;
}

void initAC(void)
{
    //Select DACREF Source (1.024V)
    VREF.ACREF = VREF_REFSEL_1V024_gc;
    
    //Inverted Output, Initial Value Low, AINP1 (PD3), DACREF
    AC1.MUXCTRL = AC_INVERT_bm | AC_INITVAL_LOW_gc | AC_MUXPOS_AINP1_gc | AC_MUXNEG_DACREF_gc;
    
    //Divider Ratio 1:11
    //Set DACREF at ~45mV
    AC1.DACREF = 113;
    
    //Enable output to pin (debug), slow response, med. hysteresis, Enable
    AC1.CTRLA = AC_OUTEN_bm | AC_POWER_PROFILE2_gc | AC_HYSMODE_MEDIUM_gc | AC_ENABLE_bm;
}
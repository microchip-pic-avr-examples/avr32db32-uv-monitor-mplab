#include "OPAMP.h"

#include <xc.h>

void OPAMP_init(void)
{    
    //Enable Run in Debug
    OPAMP.DBGCTRL = OPAMP_DBGRUN_bm;
    
    //Number of CLK_PER cycles to wait for >= 1us
    //CLK_PER = 4 MHz, 4 cycles
    OPAMP.TIMEBASE = 4;
    
    //OPAMP 0 Settings (DAC Output Buffer) - Uses PD2
    
    //Gain of 4, Bottom Mux is Ground, Top Mux is OPAMP Output
    OPAMP.OP0RESMUX = OPAMP_OP0RESMUX_MUXWIP_WIP5_gc | OPAMP_OP0RESMUX_MUXBOT_GND_gc | OPAMP_OP0RESMUX_MUXTOP_OUT_gc;
    
    //In- = Resistor Ladder, In+ = DAC Output
    OPAMP.OP0INMUX = OPAMP_OP0INMUX_MUXNEG_WIP_gc| OPAMP_OP0INMUX_MUXPOS_DAC_gc;
    
    //Output Driver ON
    OPAMP.OP0CTRLA = OPAMP_OUTMODE0_bm;
    
    //Settling Time (Set to 127us, max value)
    OPAMP.OP0SETTLE = 0x7F;
    
    //Enable the OPAMP Peripheral
    OPAMP.CTRLA |= OPAMP_ENABLE_bm;  
}

void OPAMP_enableDACBuffer(void)
{
    //Enable OPAMP 0
    OPAMP.OP0CTRLA |= OPAMP_ALWAYSON_bm;
}

void OPAMP_disableDACBuffer(void)
{
    
    //Disable OPAMP 0
    OPAMP.OP0CTRLA &= ~OPAMP_ALWAYSON_bm;
}

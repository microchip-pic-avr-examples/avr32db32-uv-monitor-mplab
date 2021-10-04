#include "TCD.h"
#include "../utility.h"

#include <xc.h>

void TCD_init(void)
{    
    //OSCHF (4MHz), No Divider
    TCD0.CTRLA = 0x00;
    
    //Output Mode: 1 Ramp
    TCD0.CTRLB = TCD_WGMODE_ONERAMP_gc;
    
    //Enable Run in Debug
    TCD0.DBGCTRL = TCD_DBGRUN_bm;

    //F_TCD = f_CLK / (CMPBCLR + 1)
    //Frequency: 100kHz
    TCD0.CMPBCLR = 39;
    
    //Start WO A immediately
    TCD0.CMPASET = 0;
    
    //Power Supply Startup: 10%
    TCD0.CMPACLR = 4;
    
    //25% duty cycle for LEDs
    TCD0.CMPBSET = 0;
    
    //Ready the Peripheral
    TCD0.STATUS = TCD_ENRDY_bm;
}
    
void TCD_start(void)
{
    //Enable TCD
    TCD0.CTRLA |= TCD_ENABLE_bm;
}

void TCD_stop(void)
{
    //Disable TCD
    TCD0.CTRLA &= ~(TCD_ENABLE_bm);
}

//Increase Duty Cycle by 1
void TCD_incrementDutyCycle(void)
{
    //while (TCD0.STATUS & TCD_CMDRDY_bm);
    TCD0.CMPACLR++;
}

//Decrease Duty Cycle by 1
void TCD_decrementDutyCycle(void)
{
    //while (TCD0.STATUS & TCD_CMDRDY_bm);
    TCD0.CMPACLR--;
}

//Get CMPCLRA (which is the duty cycle)
uint16_t TCD_getDutyCycle(void)
{
    return TCD0.CMPACLR;
}

void TCD_setCMPCLRA(uint16_t value)
{
    //while (TCD0.STATUS & TCD_CMDRDY_bm);
    TCD0.CMPACLR = value;
}

uint16_t TCD_getCMPCLRA(void)
{
    return TCD0.CMPACLR;
}

void TCD_syncChanges(void)
{
    //Wait for CMDRDY to be set
    while (!((TCD0.STATUS & TCD_CMDRDY_bm) >> TCD_CMDRDY_bp));
    TCD0.CTRLE = TCD_SYNC_bm;
}
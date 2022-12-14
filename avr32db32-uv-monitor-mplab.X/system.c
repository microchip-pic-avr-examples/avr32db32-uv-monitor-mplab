#include "system.h"

#include "peripherals/CLKCTRL.h"
#include "peripherals/SLPCTRL.h"
#include "peripherals/IO.h"
#include "peripherals/TCD.h"
#include "peripherals/CCL.h"
#include "peripherals/AC.h"
#include "peripherals/EVSYS.h"
#include "peripherals/TCB.h"
#include "peripherals/RTC.h"
#include "peripherals/TWI0_host.h"
#include "peripherals/ADC.h"
#include "peripherals/TCA0.h"
#include "display.h"

static volatile SYSTEM_EVENT event;

void SYSTEM_initPeripherals(void)
{
    event = SYSTEM_NONE;
    
    //Setup CPU Clocks
    CLKCTRL_init();
    
    //Init Sleep Controls
    SLPCTRL_init();
    
    //Init Device I/O 
    IO_init();
        
    //Init TCD
    TCD_init();
    
    //Init TCA
    TCA0_init();
    
    //Init CCL
    CCL_init();
    
    //Init AC
    AC_init();
    
    //Init ADC
    ADC_init();
    
    //Init the Event System
    EVSYS_init();
    
    //Init TCB
    TCB_init();
    
    //Init RTC
    RTC_init();
                
    //Init the TWI in host mode
    TWI0_initHost();
}

void SYSTEM_enterSleep(void)
{   
    //Turn off LEDs
    DISPLAY_turnOff();
    
    //Re-Enable IO Interrupts
    IO_enableButtonInterrupts();
        
    //Enter Sleep
    asm("SLEEP");
}

void SYSTEM_setSystemEvent(SYSTEM_EVENT ev)
{
    event = ev;
}

SYSTEM_EVENT SYSTEM_getSystemEvent(void)
{
    return event;
}

void SYSTEM_clearSystemEvent(void)
{
    event = SYSTEM_NONE;
}
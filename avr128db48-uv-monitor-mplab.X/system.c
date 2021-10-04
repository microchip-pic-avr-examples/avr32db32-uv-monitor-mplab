#include "system.h"

#include "peripherals/CLKCTRL/CLKCTRL.h"
#include "peripherals/SLPCTRL/SLPCTRL.h"
#include "peripherals/IO.h"
#include "peripherals/TCD/TCD.h"
#include "peripherals/CCL/CCL.h"
#include "peripherals/AC/AC.h"
#include "peripherals/EVSYS/EVSYS.h"
#include "peripherals/TCB/TCB.h"
#include "peripherals/RTC/RTC.h"
#include "peripherals/DAC/DAC.h"
#include "peripherals/TWI/TWI.h"
#include "peripherals/OPAMP/OPAMP.h"

void initPeripherals(void)
{
    //Setup CPU Clocks
    CLKCTRL_init();
    
    //Init Sleep Controls
    SLPCTRL_init();
    
    //Init Device I/O 
    IO_init();
    
    //Init TCD
    TCD_init();
    
    //Init CCL
    CCL_init();
    
    //Init AC
    AC_init();
    
    //Init the Event System
    EVSYS_init();
    
    //Init TCB
    TCB_init();
    
    //Init RTC
    RTC_init();
            
    //Init DAC
    DAC_init();
    
    //Init OPAMP(s)
    OPAMP_init();
        
    //Init the TWI in host mode
    TWI_initHost();
}
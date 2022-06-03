#include "../utility.h"

#include <xc.h>

void EVSYS_init(void)
{
    //TCD Pulse Counter Setup
    
    //Event Generator: TCD0 [CMPASET] (rising edge of TCD)
    EVSYS.CHANNEL0 = 0xB1;
    
    //Connect TCB to Event Channel 0
    EVSYS.USERTCB1COUNT = 1;
    
    //RTC Clock 
    //REMOVED - RTC OVF Interrupt used now
    
    //Event Generator: RTC Compare (OSC1K)
    //EVSYS.CHANNEL1 = 0x07;
    
    //Connect TCB to Event Channel 1
    //EVSYS.USERTCB2COUNT = 2;
    
    //Output Pulse Counter Setup
    
    //Event Generator: LUT0
    EVSYS.CHANNEL3 = 0x10;
    
    //Connect TCB (Counter) to Event Channel 3
    EVSYS.USERTCB0COUNT = 4;
    
    //Output EVOUTD
    EVSYS.USEREVSYSEVOUTD = 4;
}
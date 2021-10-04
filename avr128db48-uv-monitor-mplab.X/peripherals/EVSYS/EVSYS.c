#include "../utility.h"

#include <xc.h>

void EVSYS_init(void)
{
    //Output Pulse Counter Setup
    
    //Event Generator: LUT0
    EVSYS.CHANNEL0 = 0x10;
    
    //Connect TCB to Event Channel 0
    EVSYS.USERTCB0COUNT = 1;
    
    //TCD Pulse Counter Setup
    
    //Event Generator: TCD0 [CMPASET] (rising edge of TCD)
    EVSYS.CHANNEL1 = 0xB1;
    
    //Connect TCB to Event Channel 1
    EVSYS.USERTCB1COUNT = 2;
    
    //RTC Clock 
    
    //Event Generator: RTC (OSC1K)
    EVSYS.CHANNEL2 = 0x00;
    
    //Connect TCB to Event Channel 2
    EVSYS.USERTCB2COUNT = 3;
}
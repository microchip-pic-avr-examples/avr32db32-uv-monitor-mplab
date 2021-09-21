#ifndef TCB_H
#define	TCB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
        
    //Init TCB
    void initTCB(void);

    //Start TCB0 and TCB1
    void startOneShotCounters(void);
    
    //Set the pulse timeout
    void setPulseTimeoutTCB1(uint16_t count);
    
    //Get the number of output pulses
    uint16_t getPulseCountTCB0(void);
    
    //Halt Output Pulse Counter
    void stopOutputCounter(void);
    
    //Wait for TCB1 to finish
    void waitForPulses(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TCB_H */


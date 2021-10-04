#ifndef TCB_H
#define	TCB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
        
    //Init TCB
    void TCB_init(void);

    //Start TCB0 and TCB1
    void TCB_startOneShotCounters(void);
    
    //Set the pulse timeout
    void TCB_setPulseTimeout(uint16_t count);
    
    //Get the number of output pulses
    uint16_t TCB_getOutputPulses(void);
    
    //Halt Output Pulse Counter
    void TCB_stopOutputCounter(void);
    
    //Wait for TCB1 to finish
    void TCB_waitForPulses(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TCB_H */


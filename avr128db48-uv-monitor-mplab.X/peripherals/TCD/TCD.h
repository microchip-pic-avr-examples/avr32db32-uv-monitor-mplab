#ifndef TCD_H
#define	TCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    //Init TCD
    void TCD_init(void);
    
    //Start TCD
    void TCD_start(void);
    
    //Stop TCD
    void TCD_stop(void);
    
    //Increase Duty Cycle by 1
    void TCD_incrementDutyCycle(void);
    
    //Decrease Duty Cycle by 1
    void TCD_decrementDutyCycle(void);
    
    //Get CMPCLRA (which is the duty cycle)
    uint16_t TCD_getDutyCycle(void);
    
    //Set the Clear Count for WOA
    void TCD_setCMPCLRA(uint16_t value);
    
    //Get the clear count for WOA
    uint16_t TCD_getCMPCLRA(void);
    
    //Sync Changes 
    void TCD_syncChanges(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TCD_H */


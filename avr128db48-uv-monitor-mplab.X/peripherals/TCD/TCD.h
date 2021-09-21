#ifndef TCD_H
#define	TCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
    //Init TCD
    void initTCD(void);
    
    //Start TCD
    void startTCD(void);
    
    //Stop TCD
    void stopTCD(void);
    
    //Increase Duty Cycle by 1
    void incrementDutyCycle(void);
    
    //Decrease Duty Cycle by 1
    void decrementDutyCycle(void);
    
    //Get CMPCLRA (which is the duty cycle)
    uint16_t getDutyCycle(void);
    
    //Set the Clear Count for WOA
    void setCMPCLRA(uint16_t value);
    
    //Get the clear count for WOA
    uint16_t getCMPCLRA(void);
    
    //Sync Changes 
    void syncChanges(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TCD_H */


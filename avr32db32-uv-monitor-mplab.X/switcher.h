#ifndef SWITCHER_H
#define	SWITCHER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
//Number of pulses to wait
#define PULSE_WAIT 1000
    
#define MAX_DC 20
#define MIN_DC 1
        
    //Start the Boost Converter
    void SWITCHER_initBoost(void);
    
    //Call this function to auto-adjust the duty cycle of the TCD. Blocking.
    void SWITCHER_adjustPowerOutputBlocking(void);
    
    //Call this function periodically to adjust the duty cycle of the TCD. Non-Blocking.
    void SWITCHER_adjustPowerOutputISR(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SWITCHER_H */


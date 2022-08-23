#ifndef SWITCHER_H
#define	SWITCHER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
//Number of pulses to wait
#define PULSE_WAIT 1000
        
//Protects against a broken sense network. This sets the min. threshold for the network to be "good"
//800 = 100mV * accumulation of 8
//ADC is setup as 10-bit, 1.024VREF, 1mV per bit
#define SWITCHER_SAFETY_MIN 800
    
    //Start the Boost Converter
    void SWITCHER_initBoost(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SWITCHER_H */


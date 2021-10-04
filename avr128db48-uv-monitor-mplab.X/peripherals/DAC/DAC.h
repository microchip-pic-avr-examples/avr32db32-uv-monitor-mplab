#ifndef DAC_H
#define	DAC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
//DAC Value required to get ~3.3V out of the OPAMP at a gain of 4
#define DAC_DEFAULT 325
    
    //Initialize the DAC peripheral
    void DAC_init(void);
    
    //Enable the DAC
    void DAC_enable(void);
    
    //Turn off the DAC
    void DAC_disable(void);
    
    //Get the 10-bit value in the DAC
    uint16_t DAC_getValue(void);
    
    //Set the 10-bit value in the DAC
    void DAC_setValue(uint16_t value);
    
#ifdef	__cplusplus
}
#endif

#endif	/* DAC_H */


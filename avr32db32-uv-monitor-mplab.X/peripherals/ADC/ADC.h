#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    //Init the ADC
    void ADC_init(void);
    
    //Sets the sampling channel of the ADC
    void ADC_setSamplingChannel(uint8_t channel);
    
    //Starts an ADC Conversion
    void ADC_startConversion(void);
    
    //Returns true if the ADC is converting
    bool ADC_isBusy(void);
    
    //Read the result accumulation register of the ADC
    uint16_t ADC_getAccumulation(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


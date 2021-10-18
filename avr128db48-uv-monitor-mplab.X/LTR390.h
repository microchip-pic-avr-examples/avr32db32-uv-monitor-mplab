#ifndef LTR390_H
#define	LTR390_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "LTR390_registers.h"
    
#include <stdint.h>
#include <stdbool.h>
    
//If defined, a SW Reset command is sent to LTR390 on Init
#define SW_RESET  
    
//Window Factor
    
//If defined - UV Index Result is multiplied by this factor
//#define WFAC 1.0
    
//Sensitivity of LTR390 (UVI / Bits)    
//18-bits, 18x gain (see data sheet)
#define UVI_SENSITIVITY 2300
    
    //Reset and Configure LTR-390 Sensor
    bool initLTR390(void);
    
    //Set a register in the LTR390 
    bool LTR390_setRegister(LTR390_REGISTER reg, uint8_t config);
    
    //Set a 24-bit register in the LTR390
    bool LTR390_setRegister24B(LTR390_REGISTER reg, uint8_t upperByte, uint8_t highByte, uint8_t lowByte);
    
    //Get a 24-bit register in the LTR390. Value should point to an array of 3 bytes
    bool LTR390_getRegister24B(LTR390_REGISTER reg, uint8_t* value);
    
    //Get a register in the LTR390
    uint8_t LTR390_getRegister(LTR390_REGISTER reg);
        
    //Returns true if the P/N Field matches the Datasheet
    bool LTR390_isConnected(void);
    
    //Compute the UV Index of the Sensor
    uint8_t calculateUVIndex(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* LTR390_H */


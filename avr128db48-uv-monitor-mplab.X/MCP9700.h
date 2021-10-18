#ifndef MCP9700_H
#define	MCP9700_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
//Temperature output at 0C (in mV)
#define MCP9700_OFFSET 500
    
//Temperature Coefficent in mV/C
#define MCP9700_TEMPCO 10.0
    
    //Configure the ADC to measure the output of the MCP9700
    void MCP9700_init(void);

    //Returns the temperature of the MCP9700 in Celsius 
    uint8_t MCP9700_measureTemperature(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* MCP9700_H */


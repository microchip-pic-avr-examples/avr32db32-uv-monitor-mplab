#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Configures Device I/O
    void IO_init(void);
    
    //Turn on LEDs
    void IO_setLEDs(uint8_t value);
    
    //Disable Falling Edge Interrupts from Buttons
    void IO_disableButtonInterrupts(void);
    
    //Enable Falling Edge Interrupts from Buttons
    void IO_enableButtonInterrupts(void);
    
    //Enables the DAC + OPAMP to Power-Up the MVIO Port
    void MVIO_enable(void);
    
    //Disables the DAC + OPAMP to Power-Down the MVIO Port
    void MVIO_disable(void);

#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */


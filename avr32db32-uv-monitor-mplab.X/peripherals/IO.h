#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
#define IO_ENABLE_MCP9700() { PORTD.OUTSET = PIN5_bm; }
#define IO_DISABLE_MCP9700() { PORTD.OUTCLR = PIN5_bm; }
    
#define IO_ENABLE_3V3() { PORTF.OUTSET = PIN2_bm; }
#define IO_DISABLE_3V3() { PORTF.OUTCLR = PIN2_bm; }
    
#define UV_BUTTON_GET_STATE() (VPORTD.IN & PIN6_bm)
#define TEMP_BUTTON_GET_STATE() (VPORTD.IN & PIN7_bm)
    
//#define DEBUG_PWM
    
    //Configures Device I/O
    void IO_init(void);
    
    //Turn on LEDs
    void IO_setLEDs(uint8_t value);
    
    //Disable Falling Edge Interrupts from Buttons
    void IO_disableButtonInterrupts(void);
    
    //Enable Falling Edge Interrupts from Buttons
    void IO_enableButtonInterrupts(void);

#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */


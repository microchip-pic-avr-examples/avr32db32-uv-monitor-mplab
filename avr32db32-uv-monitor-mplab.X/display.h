#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>

    //Sets the maximum position on the LED display
    void DISPLAY_setMaxPosition(uint8_t outVal);

    //Sets which LED should be on. Animation will increment from this position
    void DISPLAY_setAnimationPosition(uint8_t val);
        
    //Turns off the display
    void DISPLAY_turnOff(void);
    
    //Turns on TCA for the LED display, then displays the current value
    void DISPLAY_turnOn(void);
    
    //Shows the display, but does not update values
    void DISPLAY_show(void);
    
    //Disables LED control / animations
    void DISPLAY_disableAnimation(void);
    
    //Enables LED control / animation
    void DISPLAY_enableAnimation(void);
    
    //Resets the display animation
    void DISPLAY_reset(void);
    
    //Run the rotary animation
    void DISPLAY_updateAnimation(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */


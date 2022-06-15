#include "display.h"
#include "peripherals/IO.h"
#include "RTC.h"
#include "TCA0.h"

#include <stdint.h>
#include <stdbool.h>

//Sets the max value for the display to reach
static volatile uint8_t displayMax = 0x00;

//Current position of the lit segment
static volatile uint8_t currentDisplay = 0x00;

static volatile bool runAnimation = false;

//Sets the LED
void DISPLAY_setMaxPosition(uint8_t outVal)
{
    displayMax = outVal;
    currentDisplay = 0;
    
    DISPLAY_show();
}

//Sets which LED should be on. Animation will increment from this position
void DISPLAY_setAnimationPosition(uint8_t val)
{
    currentDisplay = val;
}

//Turns off the display
void DISPLAY_turnOff(void)
{
    TCA0_stop();
    IO_setLEDs(0x00);
}

//Starts LED PWM
void DISPLAY_turnOn(void)
{
    TCA0_start();
    DISPLAY_show();
}

//Shows the display, but does not update values
void DISPLAY_show(void)
{
    uint8_t LEDmask = 0;
    
    //If at the max position of the LEDs
    if ((currentDisplay == displayMax) || (currentDisplay >= 8))
    {
        //Reset Value
        currentDisplay = 0;
    }
    
    //Set LED mask
    //LEDmask <<= currentDisplay;
    
    //Show Maximum as a static display
    LEDmask |= (0b1 << displayMax);
    
    //Update LEDs
    IO_setLEDs(LEDmask);

}

//Disables LED control / animations
void DISPLAY_disableAnimation(void)
{
    runAnimation = false;
}

//Enables LED control / animation
void DISPLAY_enableAnimation(void)
{
    runAnimation = true;
}

//Resets the display animation
void DISPLAY_reset(void)
{
    currentDisplay = 0;
    displayMax = 8;
    runAnimation = true;
}

//Run the rotary animation
void DISPLAY_updateAnimation(void)
{
    //If animations are disabled
    if (!runAnimation)
    {
        return;
    }
      
    //Increment LED Position
    currentDisplay++;
    
    //Show Display
    DISPLAY_show();
}

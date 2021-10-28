#include "IO.h"
#include "utility.h"
#include "TCD/TCD.h"
#include "../system.h"

#include <xc.h>

//Configures Device I/O
void IO_init(void)
{
    //AC 
    {
        //Set as analog input (PD3)
        PORTD.DIRCLR = PIN3_bm;

        //Disable Digital Input Buffer
        PORTD.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
    }
    
    //ADC
    {
        //PD5 (AIN5)
        
        //Set PD5 as an input
        PORTD.DIRCLR = PIN5_bm;
        
        //Disable Digital Input Buffer
        PORTD.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
    }
    
    //CCL 
    {
        //Output is via EVOUTD (PD2)
        PORTD.DIRSET = PIN2_bm;
    }
    
    //DAC 
    {
        //Configure Output Pin PD6 (Analog Output)
        //PORTD.DIRSET = PIN6_bm;
        //PORTD.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
    }
    
    //TCD
    {
        //Use PF0, PF1, PF2, PF3
        PORTMUX.TCDROUTEA = PORTMUX_TCD0_ALT2_gc;
        
        //LED PWM Output
        PORTF.OUTCLR = PIN1_bm;
        PORTF.DIRSET = PIN1_bm;
        _PROTECTED_WRITE(TCD0.FAULTCTRL, TCD_CMPBEN_bm);  
        
#ifndef DEBUG_PWM
        
        //PF0 - PWM Output (WOA). Debug Only
        PORTF.OUTCLR = PIN0_bm;
        PORTF.DIRSET = PIN0_bm;
        
        //Enable WO-A
        _PROTECTED_WRITE(TCD0.FAULTCTRL, TCD_CMPAEN_bm | TCD_CMPBEN_bm);
#endif      
    }
    
    //TWI 
    {
        //PC2/PC3
        PORTMUX.TWIROUTEA = PORTMUX_TWI0_ALT2_gc;
        
        //Output I/O
        PORTC.DIRSET = PIN2_bm | PIN3_bm;

        //Enable Pull-Ups
        PORTC.PINCONFIG = PORT_PULLUPEN_bm;

        //Select RC2/RC3
        PORTC.PINCTRLUPD = PIN2_bm | PIN3_bm;
    }
    
    //LED I/O 
    {
        //PORTA is LED Outputs
        PORTA.DIRSET = 0xFF;
        
        //Turn off LEDs (active low)
        PORTA.OUTSET = 0xFF;
    }
    
    //Interrupt on Change I/O
    {
        //D6, D7 - Buttons
        //D6 = UV Start
        //D7 = Temp Start
        
        PORTD.DIRCLR = PIN6_bm | PIN7_bm;
        
        //Pull-up Enabled, Falling Edge Triggered
        PORTD.PIN6CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
        
        //Pull-up Enabled, Falling Edge Triggered
        PORTD.PIN7CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
    }
}

void IO_setLEDs(uint8_t value)
{
    //LED Outputs (LSB -> MSB)
    //Port A
    PORTA.OUTSET = 0xFF;
    PORTA.OUTCLR = value;
}

//Disable Rising Edge Interrupts from Buttons
void IO_disableButtonInterrupts(void)
{
    PORTD.PIN6CTRL &= ~PORT_ISC_gm;
    PORTD.PIN7CTRL &= ~PORT_ISC_gm;
}

//Enable Rising Edge Interrupts from Buttons
void IO_enableButtonInterrupts(void)
{
    PORTD.PIN6CTRL |= PORT_ISC_FALLING_gc;
    PORTD.PIN7CTRL |= PORT_ISC_FALLING_gc;
}

void __interrupt(PORTD_PORT_vect_num) _PinIOC(void)
{
    //Disable IO Interrupts
    IO_disableButtonInterrupts();
    
    //Only 1 measurement is active at a time. Prioritize UV over Temp
    //Start in the Wait State to sync the state machine with the RTC
    if (PORTD.INTFLAGS & PIN6_bm)
    {
        //PD6 pressed 
        setSystemEvent(UV_MEAS);
    }
    else if (PORTD.INTFLAGS & PIN7_bm)
    {
        //PD7 pressed 
        setSystemEvent(TEMP_MEAS);
    }
        
    //Clear all flags
    PORTD.INTFLAGS = PIN6_bm | PIN7_bm;
    
}
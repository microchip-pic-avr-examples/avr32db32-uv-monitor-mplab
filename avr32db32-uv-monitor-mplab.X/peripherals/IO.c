#include "IO.h"
#include "TCD.h"
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
        //PD4 (AIN4)
        
        //Set PD4 as an input
        PORTD.DIRCLR = PIN4_bm;
        
        //Disable Digital Input Buffer
        PORTD.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
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
    
    //TCA
    {
        //LED PWM
        //PF1
        PORTF.OUTSET = PIN1_bm;
        PORTF.DIRSET = PIN1_bm;
        
        PORTF.PIN1CTRL = PORT_INVEN_bm;
        
        //Select PORT-F
        PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTF_gc;
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
    
    //MCP9700 Power
    {
        //PD5
        PORTD.DIRSET = PIN5_bm;
    }
    
    //3.3V Enable
    {
        //PF2 
        PORTF.DIRSET = PIN2_bm;
    }
    
    //Interrupt on Change I/O
    {
        //D6, D7 - Buttons
        //D6 = UV Start
        //D7 = Temp Start
        
        PORTD.DIRCLR = PIN6_bm | PIN7_bm;
        
        //Inverted Levels, TTL, Pull-ups
        PORTD.PIN6CTRL = PORT_INVEN_bm | PORT_INLVL_bm | PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;
        
        //Inverted Levels, TTL, Pull-ups
        PORTD.PIN7CTRL = PORT_INVEN_bm | PORT_INLVL_bm | PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;  
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
    PORTD.PINCONFIG = PIN6_bm | PIN7_bm;
    PORTD.PINCTRLCLR = PORT_ISC_RISING_gc;
}

//Enable Rising Edge Interrupts from Buttons
void IO_enableButtonInterrupts(void)
{
    //Clear any pending flags
    PORTD.INTFLAGS = PIN6_bm | PIN7_bm;
    
    IO_disableButtonInterrupts();

    //Re-enable
    PORTD.PINCONFIG = PIN6_bm | PIN7_bm;
    PORTD.PINCTRLSET = PORT_ISC_RISING_gc;
}

void __interrupt(PORTD_PORT_vect_num) _PinIOC(void)
{
    //Disable IO Interrupts
    IO_disableButtonInterrupts();
    
    if (PORTD.INTFLAGS & PIN6_bm)
    {
        //PD6 pressed 
        SYSTEM_setSystemEvent(UV_BUTTON);
    }
    else if (PORTD.INTFLAGS & PIN7_bm)
    {
        //PD7 pressed 
        SYSTEM_setSystemEvent(TEMP_BUTTON);
    }
        
    //Clear all flags
    PORTD.INTFLAGS = PIN6_bm | PIN7_bm;
}
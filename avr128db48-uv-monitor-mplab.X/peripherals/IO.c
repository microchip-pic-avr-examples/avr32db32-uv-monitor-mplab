#include "IO.h"
#include "utility.h"
#include "OPAMP/OPAMP.h"
#include "DAC/DAC.h"

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

        //Enable Output Buffer (PA7)
        PORTA.DIRSET = PIN7_bm;
    }
    
    //CCL 
    {
        //Use Alt. Pin Location (PA6) for LUT0 Out
        PORTMUX.CCLROUTEA = PORTMUX_LUT0_ALT1_gc;
    }
    
    //DAC 
    {
        //Configure Output Pin PD6 (Analog Output)
        PORTD.DIRSET = PIN6_bm;
        PORTD.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
    }
    
    //TCD (Debug Only)
    {
        /*
        //PA4 - PWM Output
        PORTA.OUTCLR = PIN4_bm;
        PORTA.DIRSET = PIN4_bm;

        //Enable WO-A
        UNLOCK_CCP();
        TCD0.FAULTCTRL = TCD_CMPAEN_bm;
         */
        
        //PA5 - LED Output
        PORTA.OUTCLR = PIN5_bm;
        PORTA.DIRSET = PIN5_bm;
        
        UNLOCK_CCP();
        TCD0.FAULTCTRL |= TCD_CMPBEN_bm | TCD_CMPB_bm;
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
    
    //Discrete I/O 
    {
        //LED0 on Nano (PB3)
        PORTB.DIRSET = PIN3_bm;
        
        //Pushbutton on Nano (PB2)
        PORTB.DIRCLR = PIN2_bm;
       
        //Falling Edge Interrupt and Pull-Up Resistor Enabled
        PORTB.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
        
        //Turn off all LEDs
        IO_setLEDs(0x00);
        
        //LED Outputs (LSB -> MSB)
        //PF4, PF5, PA2, PA3, PA0, PA1, PB2, PB3
        PORTF.DIRSET |= PIN4_bm | PIN5_bm;
        PORTA.DIRSET |= PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
        PORTB.DIRSET |= PIN2_bm | PIN3_bm;
    }
    
}

//Enables the DAC + OPAMP and Starts the MVIO Port
void MVIO_enable(void)
{
    //Start DAC
    DAC_enable();
    
    //Start OPAMP
    OPAMP_enableDACBuffer();
}

void MVIO_disable(void)
{
    //Turn off the OPAMP
    OPAMP_disableDACBuffer();
    
    //Turn off the DAC
    DAC_disable();
}

void IO_setLEDs(uint8_t value)
{
    //LED Outputs (LSB -> MSB)
    //PF4, PF5, PA2, PA3, PA0, PA1, PB2, PB3
    
    if (value > 0)
        PORTF.OUTCLR = PIN4_bm;
    else
        PORTF.OUTSET = PIN4_bm;
    
    if (value > 1)
        PORTF.OUTCLR = PIN5_bm;
    else
        PORTF.OUTSET = PIN5_bm;
    
    if (value > 2)
        PORTA.OUTCLR = PIN2_bm;
    else
        PORTA.OUTSET = PIN2_bm;
    
    if (value > 3)
        PORTA.OUTCLR = PIN3_bm;
    else
        PORTA.OUTSET = PIN3_bm;
    
    if (value > 4)
        PORTA.OUTCLR = PIN0_bm;
    else
        PORTA.OUTSET = PIN0_bm;
    
    if (value > 5)
        PORTA.OUTCLR = PIN1_bm;
    else
        PORTA.OUTSET = PIN1_bm;
    
    if (value > 6)
        PORTB.OUTCLR = PIN2_bm;
    else
        PORTB.OUTSET = PIN2_bm;
    
    if (value > 7)
        PORTB.OUTCLR = PIN3_bm;
    else
        PORTB.OUTSET = PIN3_bm;
}
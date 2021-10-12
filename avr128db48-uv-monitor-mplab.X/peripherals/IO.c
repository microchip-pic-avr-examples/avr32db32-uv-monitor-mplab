#include "IO.h"
#include "utility.h"
#include "OPAMP/OPAMP.h"
#include "DAC/DAC.h"
#include "TCD/TCD.h"

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
        //PORTA.DIRSET = PIN7_bm;
    }
    
    //CCL 
    {
        //Use Alt. Pin Location (PA6) for LUT0 Out
        //PORTMUX.CCLROUTEA = PORTMUX_LUT0_ALT1_gc;
        
        //Output is via EVOUTD (PD2)
        PORTD.DIRSET = PIN2_bm;
    }
    
    //DAC 
    {
        //Configure Output Pin PD6 (Analog Output)
        PORTD.DIRSET = PIN6_bm;
        PORTD.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
    }
    
    //TCD (Debug Only)
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
    
    //Discrete I/O 
    {
        //PORTA is the output
        PORTA.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm |
                PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm;
    }
    
}

//Enables the DAC + OPAMP and Starts the MVIO Port
void MVIO_enable(void)
{
    return;
    
    //Start DAC
    DAC_enable();
    
    //Start OPAMP
    OPAMP_enableDACBuffer();
}

void MVIO_disable(void)
{
    return;
    
    //Turn off the OPAMP
    OPAMP_disableDACBuffer();
    
    //Turn off the DAC
    DAC_disable();
}

void IO_setLEDs(uint8_t value)
{
    //LED Outputs (LSB -> MSB)
    //PF4, PF5, PA2, PA3, PA0, PA1, PB2, PB3
    PORTA.OUTCLR = 0xFF;
    PORTA.OUTSET = value;
}
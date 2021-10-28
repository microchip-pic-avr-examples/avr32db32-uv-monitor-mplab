/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

#include <xc.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "switcher.h"
#include "LTR390.h"
#include "system.h"
#include "results.h"

#include "peripherals/RTC/RTC.h"
#include "peripherals/ADC/ADC.h"
#include "MCP9700.h"

FUSES = {
	.WDTCFG = 0x00, // WDTCFG {PERIOD=OFF, WINDOW=OFF}
	.BODCFG = 0x06, // BODCFG {SLEEP=SAMPLE, ACTIVE=ENABLE, SAMPFREQ=128Hz, LVL=BODLEVEL0}
	.OSCCFG = 0x00, // OSCCFG {CLKSEL=OSCHF}
	.SYSCFG0 = 0xC8, // SYSCFG0 {EESAVE=CLEAR, RSTPINCFG=RST, CRCSEL=CRC16, CRCSRC=NOCRC}
	.SYSCFG1 = 0x0C, // SYSCFG1 {SUT=8MS, MVSYSCFG=DUAL}
	.CODESIZE = 0x00, // CODESIZE {CODESIZE=User range:  0x0 - 0xFF}
	.BOOTSIZE = 0x00, // BOOTSIZE {BOOTSIZE=User range:  0x0 - 0xFF}
};

LOCKBITS = 0x5CC5C55C; // {KEY=NOLOCK}

#define PIT_WAIT 4

void handlePITEvent(void)
{
    static uint8_t UV_wait = 0;
    //Handle Periodic Interrupt Timer Events
    
    //If waiting, advance state machine
    if (getSystemEvent() == WAIT_UV)
    {
        UV_wait++;
        if (UV_wait >= PIT_WAIT)
        {
            setSystemEvent(TIMER_UV);
            UV_wait = 0;
        }
            
    }
    else if (getSystemEvent() == WAIT_TEMP)
    {
        setSystemEvent(TIMER_TEMP);
    }
    
    //Adjust Power Supply
    adjustPowerOutputISR();
}

//About 10 seconds
#define SAMPLES_UV 20
#define SAMPLES_TEMP 20

int main(void)
{   
    //Init Peripherals
    initPeripherals();
    
    //Configure the Boost
    initBoost();
    
    //On Power-Up, Adjust Duty Cycle
    adjustPowerOutputBlocking();
    
    //Connect the PIT Interrupt to the Power Adjustment Function
    PIT_setISR(&handlePITEvent);
        
    //Enable Interrupts
    sei();
    
    //Init LTR390
    LTR390_init();
         
    //Init Peripherals for MCP9700
    MCP9700_init();
    
    uint8_t timeCount = 0;
    
    while (1)
    {   
        switch(getSystemEvent())
        {
            case SYSTEM_NONE:
            {
                enterSleep();
                break;
            }
            case UV_MEAS:
            {
                //Measure UV and Update Display
                UV_getAndDisplayResults();
                
                //Update State Machine
                setSystemEvent(WAIT_UV);
                break;
            }
            case TEMP_MEAS:
            {
                //Measure Temperature and Update Display
                TEMP_getAndDisplayResults();
                
                //Update State Machine
                setSystemEvent(WAIT_TEMP);
                break;
            }
            case WAIT_UV:
            {
                //Do Nothing...
                break;
            }
            case WAIT_TEMP:
            {
                //Do Nothing (Wait for Event to Update)
                break;
            }
            case TIMER_UV:
            {
                //Increment Counter
                timeCount++;
                
                //If at duration limit, turn off display
                if (timeCount == SAMPLES_UV)
                {
                    timeCount = 0;
                    setSystemEvent(SYSTEM_NONE);
                }
                else
                {
                    setSystemEvent(UV_MEAS);
                }
                break;
            }
            case TIMER_TEMP:
            {
                //Increment Counter
                timeCount++;
                
                //If at duration limit, turn off display
                if (timeCount == SAMPLES_TEMP)
                {
                    timeCount = 0;
                    setSystemEvent(SYSTEM_NONE);
                }
                else
                {
                    setSystemEvent(TEMP_MEAS);
                }
                
                break;
            }
        }
    }
}

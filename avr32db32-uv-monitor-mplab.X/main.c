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

#include "peripherals/RTC.h"
#include "peripherals/ADC.h"
#include "MCP9700.h"
#include "peripherals/TCD.h"
#include "peripherals/IO.h"
#include "display.h"
#include "softwareTimer.h"
#include "peripherals/TCA0.h"
#include "HTU21D.h"

FUSES = {
	.WDTCFG = 0x00, // WDTCFG {PERIOD=OFF, WINDOW=OFF}
	.BODCFG = 0x0A, // BODCFG {SLEEP=SAMPLE, ACTIVE=SAMPLE, SAMPFREQ=128Hz, LVL=BODLEVEL0}
	.OSCCFG = 0x00, // OSCCFG {CLKSEL=OSCHF}
	.SYSCFG0 = 0xD8, // SYSCFG0 {EESAVE=CLEAR, RSTPINCFG=RST, UPDIPINCFG=UPDI, CRCSEL=CRC16, CRCSRC=NOCRC}
	.SYSCFG1 = 0x0C, // SYSCFG1 {SUT=8MS, MVSYSCFG=DUAL}
	.CODESIZE = 0x00, // CODESIZE {CODESIZE=User range:  0x0 - 0xFF}
	.BOOTSIZE = 0x00, // BOOTSIZE {BOOTSIZE=User range:  0x0 - 0xFF}
};

LOCKBITS = 0x5CC5C55C; // {KEY=NOLOCK}

//Timings
#define PERIOD_RTC_QS 64
#define PERIOD_RTC_1S 256
#define PERIOD_RTC_10S 2560

int main(void)
{   
    //Init Peripherals
    SYSTEM_initPeripherals();
    
    //Configure the Boost
    SWITCHER_initBoost();
        
    //Current System State
    SYSTEM_STATE state;
    
    //Enable IOC
    IO_enableButtonInterrupts();
    
    //Enable Interrupts
    sei();
    
    //Init Peripherals for MCP9700
    MCP9700_init();
        
    //1s Period
    SW_Timer_setPeriod(PERIOD_RTC_1S);
    
    if ((TEMP_BUTTON_IS_PRESSED()) || (UV_BUTTON_IS_PRESSED()))
    {
        //A button is being pressed!
        state = SYSTEM_EVENT_ON_START;
    }
    else
    {
        state = SYSTEM_IDLE;
    }
    
    while (1)
    {   
        switch (state)
        {
            case SYSTEM_IDLE:
            {
                //Enter Sleep
                SYSTEM_enterSleep();
                if (SYSTEM_getSystemEvent() == TEMP_BUTTON)
                {
                    state = TEMP_PWR_UP;
                    IO_ENABLE_MCP9700();
                    IO_ENABLE_3V3();
                    
                    SW_Timer_reset();
                    SYSTEM_clearSystemEvent();
                }
                else if (SYSTEM_getSystemEvent() == UV_BUTTON)
                {
                    state = UV_PWR_UP;
                    IO_ENABLE_3V3();
                    
                    SW_Timer_reset();
                    SYSTEM_clearSystemEvent();
                }
                break;
            }
            case SYSTEM_EVENT_ON_START:
            {
                //This state only happens if the user is holding a button on startup
                if (TEMP_BUTTON_IS_PRESSED())
                {
                    state = TEMP_PWR_UP;
                    IO_ENABLE_MCP9700();
                    IO_ENABLE_3V3();
                    
                    SW_Timer_reset();
                    SYSTEM_clearSystemEvent();
                }
                else if (UV_BUTTON_IS_PRESSED())
                {
                    state = UV_PWR_UP;
                    IO_ENABLE_3V3();
                    
                    SW_Timer_reset();
                    SYSTEM_clearSystemEvent();
                }
                else
                {
                    //Nothing happened
                    state = SYSTEM_IDLE;
                    SYSTEM_clearSystemEvent();
                }
                break;
            }
            case UV_PWR_UP:
            {
                //UV Button Pressed

                //Warm-Up Done
                if (SW_Timer_hasTriggered())
                {
                    DISPLAY_reset();
                    DISPLAY_turnOn();
                    
                    //Init LTR390
                    if (LTR390_init())
                    {
                        state = UV_MEAS;
                    }
                    else
                    {
                        state = SENSOR_OFF;
                    }
                }
                
                break;
            }
            case TEMP_PWR_UP:
            {
                //TEMP Button Pressed
                
                //Warm-Up Done
                if (SW_Timer_hasTriggered())
                {
                    DISPLAY_reset();
                    DISPLAY_turnOn();
                    
                    if (HTU21D_init())
                    {
                        state = TEMP_MEAS;
                    }
                    else
                    {
                        state = SENSOR_OFF;
                    }
                }
                
                break;
            }
            case TEMP_MEAS:
            {
                //Begin TEMP Measurement
                HeatIndex_getAndDisplayResults();
                SW_Timer_reset();
                state = TEMP_WAIT;
                break;
            }
            case TEMP_WAIT:
            {
                if (SW_Timer_hasTriggered())
                {
                    if (TEMP_BUTTON_IS_PRESSED())
                    {
                        state = SENSOR_OFF;
                    }
                    else
                    {
                        state = TEMP_MEAS; 
                    }
                }
                break;
            }
            case UV_MEAS:
            {
                //Begin UV Measurement
                UV_getAndDisplayResults();
                SW_Timer_reset();
                state = UV_WAIT;
                break;
            }
            case UV_WAIT:
            {
                if (SW_Timer_hasTriggered())
                {
                    if (UV_BUTTON_IS_PRESSED())
                    {
                        state = SENSOR_OFF;
                    }
                    else
                    {
                        state = UV_MEAS;
                    }
                    
                }
                break;
            }
            case SENSOR_OFF:
            {
                //Turn-off sensors
                
                //Power off UV and TEMP
                IO_DISABLE_3V3();
                IO_DISABLE_MCP9700();
                
                DISPLAY_disableAnimation();
                DISPLAY_turnOff();
                
                //Debounce Time = 250ms (1/4s)
                SW_Timer_setPeriod(PERIOD_RTC_QS);
                
                //Reset SW Timer
                SW_Timer_reset();
                
                //Switch to state
                state = SYSTEM_DEBOUNCE;
                break;
            }
            case SYSTEM_DEBOUNCE:
            {
                if ((TEMP_BUTTON_IS_PRESSED()) || (UV_BUTTON_IS_PRESSED()))
                {
                    SW_Timer_reset();
                }
                if (SW_Timer_hasTriggered())
                {    
                    //Timer is done - return to sleep
                    SW_Timer_setPeriod(PERIOD_RTC_1S);
                    state = SYSTEM_IDLE;
                }
                break;
            }
        }
        
        //Update the SW Timer
        SW_Timer_addTime();        
    }
}

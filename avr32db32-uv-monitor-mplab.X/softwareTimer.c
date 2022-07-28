#include "softwareTimer.h"

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdio.h>

#include "peripherals/RTC.h"

//Last-time RTC was checked
static uint16_t lTime = 0;

//Elapsed Count
static uint16_t cycleCount = 0;

//Timeout Period
static uint16_t timeoutPeriod = 0;

//Set the number of cycles (from the RTC)
void SW_Timer_setPeriod(uint16_t period)
{
    timeoutPeriod = period;
}

//Add the current delta from the RTC
void SW_Timer_addTime(void)
{
    //If rolled over, skip time increment
    if (SW_Timer_hasTriggered())
        return;
    
    if (timeoutPeriod == 0)
        return;
    
    volatile uint16_t cTime = RTC_getCount();
    
    if (cTime >= lTime)
    {
        //Has not rolled over
        cycleCount += (cTime - lTime);
    }
    else
    {
        //Has rolled over
        cycleCount += (RTC_getPeriod() - lTime) + cTime;
    }
    
    lTime = cTime;
}

//Sets the starting count of the RTC
void SW_Timer_setCurrentTime(void)
{
    lTime = RTC_getCount();
}

//Resets the BLE_SW_Timer
//Clear Trigger Flag and Count
void SW_Timer_reset(void)
{
    cycleCount = 0;
    lTime = RTC_getCount();
}

//Returns true if the timer has triggered
bool SW_Timer_hasTriggered(void)
{
    if (timeoutPeriod == 0)
        return false;
    
    return (cycleCount >= timeoutPeriod);
}
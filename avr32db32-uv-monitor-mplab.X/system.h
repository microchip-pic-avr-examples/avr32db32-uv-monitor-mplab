#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
        SYSTEM_NONE = 0x00, TEMP_BUTTON, UV_BUTTON
    } SYSTEM_EVENT;
    
    typedef enum {
        SYSTEM_IDLE = 0x00, SYSTEM_EVENT_ON_START, UV_PWR_UP, TEMP_PWR_UP, TEMP_MEAS, 
                UV_MEAS, TEMP_WAIT, UV_WAIT, SENSOR_OFF, SYSTEM_DEBOUNCE
    } SYSTEM_STATE;
    
    //Initialize Peripherals
    void SYSTEM_initPeripherals(void);
    
    //Enter Sleep Mode
    void SYSTEM_enterSleep(void);
    
    //Set a flag if an event occurs
    void SYSTEM_setSystemEvent(SYSTEM_EVENT ev);
    
    //Get the flag from an event
    SYSTEM_EVENT SYSTEM_getSystemEvent(void);
    
    //Clear the set flag
    void SYSTEM_clearSystemEvent(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */


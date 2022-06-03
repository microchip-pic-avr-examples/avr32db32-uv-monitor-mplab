#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
        SYSTEM_NONE = 0x00, TEMP_BUTTON, UV_BUTTON
    } SYSTEM_EVENT;
    
    typedef enum {
        SYSTEM_IDLE = 0x00, UV_PWR_UP, TEMP_PWR_UP, TEMP_MEAS, UV_MEAS, SENSOR_OFF, SYSTEM_DISPLAY_RESULTS
    } SYSTEM_STATE;
    
    void SYSTEM_initPeripherals(void);
    
    void SYSTEM_enterSleep(void);
    
    void SYSTEM_setSystemEvent(SYSTEM_EVENT ev);
    SYSTEM_EVENT SYSTEM_getSystemEvent(void);
    void SYSTEM_clearSystemEvent(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */


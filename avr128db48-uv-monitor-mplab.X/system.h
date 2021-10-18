#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
        SYSTEM_NONE = 0x00, UV_MEAS, TEMP_MEAS, WAIT_UV, WAIT_TEMP, TIMER_UV, TIMER_TEMP
    } SYSTEM_EVENT;
    
    void initPeripherals(void);
    
    void enterSleep(void);
    
    void setSystemEvent(SYSTEM_EVENT ev);
    SYSTEM_EVENT getSystemEvent(void);
    void clearSystemEvent(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */


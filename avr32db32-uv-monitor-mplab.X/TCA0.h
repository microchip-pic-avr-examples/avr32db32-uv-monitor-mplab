#ifndef TCA0_H
#define	TCA0_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Init the TCA Peripheral
    void TCA0_init(void);
    
    //Start TCA
    void TCA0_start(void);
    
    //Stop TCA
    void TCA0_stop(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TCA0_H */


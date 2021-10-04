#ifndef OPAMP_H
#define	OPAMP_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void OPAMP_init(void);
    
    void OPAMP_enableDACBuffer(void);
    void OPAMP_disableDACBuffer(void);

#ifdef	__cplusplus
}
#endif

#endif	/* OPAMP_H */


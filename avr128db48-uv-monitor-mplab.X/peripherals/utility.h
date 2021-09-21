#ifndef UTILITY_H
#define	UTILITY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define UNLOCK_KEY 0xD8
#define UNLOCK_CCP() do { CPU_CCP = UNLOCK_KEY; } while (0)


#ifdef	__cplusplus
}
#endif

#endif	/* UTILITY_H */


#ifndef RESULTS_H
#define	RESULTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
//#define RESULT_DISPLAY_SOLID
#define RESULT_DISPLAY_OUTLINE
  
#define UV_LEVEL1 2
#define UV_LEVEL2 3
#define UV_LEVEL3 4
#define UV_LEVEL4 5
#define UV_LEVEL5 6
#define UV_LEVEL6 7
#define UV_LEVEL7 8
        
    void UV_getAndDisplayResults(void);
    
    void TEMP_getAndDisplayResults(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RESULTS_H */


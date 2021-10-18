#ifndef RESULTS_H
#define	RESULTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
//#define RESULT_DISPLAY_SOLID
#define RESULT_DISPLAY_OUTLINE
  
//UV Index Thresholds
#define UV_LEVEL1 2
#define UV_LEVEL2 3
#define UV_LEVEL3 4
#define UV_LEVEL4 5
#define UV_LEVEL5 6
#define UV_LEVEL6 7
#define UV_LEVEL7 8
    
//Temperature Thresholds in C
#define TEMP_LEVEL1 18
#define TEMP_LEVEL2 21
#define TEMP_LEVEL3 24
#define TEMP_LEVEL4 27
#define TEMP_LEVEL5 29
#define TEMP_LEVEL6 32
#define TEMP_LEVEL7 35
        
    //Get the UVI and Update the Display
    void UV_getAndDisplayResults(void);
    
    //Get the Current Temperature and Update the Display
    void TEMP_getAndDisplayResults(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RESULTS_H */


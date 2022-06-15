#ifndef RESULTS_H
#define	RESULTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
//#define RESULT_DISPLAY_SOLID
#define RESULT_DISPLAY_OUTLINE

//Note: LV0 is 0 
    
//UV Index Thresholds
#define UV_LEVEL1 4
#define UV_LEVEL2 5
#define UV_LEVEL3 6
#define UV_LEVEL4 7
#define UV_LEVEL5 8
#define UV_LEVEL6 9
#define UV_LEVEL7 10
    
//Temperature Thresholds in C
#define TEMP_LEVEL1 10
#define TEMP_LEVEL2 15
#define TEMP_LEVEL3 20
#define TEMP_LEVEL4 25
#define TEMP_LEVEL5 30
#define TEMP_LEVEL6 35
#define TEMP_LEVEL7 40
        
    //Get the UVI and Update the Display
    void UV_getAndDisplayResults(void);
    
    //Get the Current Temperature and Update the Display
    void TEMP_getAndDisplayResults(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* RESULTS_H */


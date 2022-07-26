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
#define UV_LEVEL1 1
#define UV_LEVEL2 2
#define UV_LEVEL3 3
#define UV_LEVEL4 4
#define UV_LEVEL5 5
#define UV_LEVEL6 6
#define UV_LEVEL7 7
    
//Temperature Thresholds in F
#define TEMP_LEVEL1 85
#define TEMP_LEVEL2 90
#define TEMP_LEVEL3 95
#define TEMP_LEVEL4 100
#define TEMP_LEVEL5 105
#define TEMP_LEVEL6 110
#define TEMP_LEVEL7 115
        
    //Get the UVI and Update the Display
    void UV_getAndDisplayResults(void);
    
    //Get the Current Temperature and Update the Display
    void TEMP_getAndDisplayResults(void);
    
    //Display the Heat Index and Update the Display
    void HeatIndex_getAndDisplayResults(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* RESULTS_H */


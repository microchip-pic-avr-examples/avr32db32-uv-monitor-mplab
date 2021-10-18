#include "results.h"

#include "peripherals/IO.h"
#include "LTR390.h"

static const uint8_t UV_thresholds[] = {0, UV_LEVEL1, UV_LEVEL2, UV_LEVEL3, UV_LEVEL4, UV_LEVEL5, UV_LEVEL6, UV_LEVEL7};

void _displayOutline(uint8_t result, const uint8_t* thresholds)
{
    uint8_t output, index;
    
    output = 0b1;
    index = 1;
    while ((index < 8) && (result >= thresholds[index]))
    {
        output = output << 1; 
        //output |= (0b1 << index);
        index++;
    }
    
    IO_setLEDs(output);
}

void _displaySolid(uint8_t result, const uint8_t* thresholds)
{
    uint8_t output, index;
    
    output = 0b0;
    index = 0;
    while ((index < 8) && (result >= thresholds[index]))
    {
        output |= (0b1 << index);
        index++;
    }
    
    IO_setLEDs(output);
}


void UV_getAndDisplayResults(void)
{
    uint8_t result = calculateUVIndex();
    
    if (result == 0xFF)
    {
        //Invalid Result...
    }
        
#ifdef RESULT_DISPLAY_OUTLINE
    _displayOutline(result, &UV_thresholds[0]);
#else
    _displaySolid(result, &UV_thresholds[0]);
#endif
}

void TEMP_getAndDisplayResults(void)
{
    
}
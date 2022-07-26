#include <avr/eeprom.h>
#include <math.h>

#include "results.h"

#include "peripherals/IO.h"
#include "LTR390.h"
#include "MCP9700.h"
#include "display.h"
#include "HTU21D.h"
#include "heatIndex.h"

static const uint8_t UV_thresholds[] = {0, UV_LEVEL1, UV_LEVEL2, UV_LEVEL3, UV_LEVEL4,
                                        UV_LEVEL5, UV_LEVEL6, UV_LEVEL7};

static const uint8_t TEMP_thresholds[] = {0, TEMP_LEVEL1, TEMP_LEVEL2, TEMP_LEVEL3,
                                        TEMP_LEVEL4, TEMP_LEVEL5, TEMP_LEVEL6, TEMP_LEVEL7};


void _displayOutline(uint8_t result, const uint8_t* thresholds)
{
    if (result == 0xFF)
    {
        DISPLAY_turnOff();
    }
    
    uint8_t output, index;
    
    //output = 0b1;
    index = 1;
    while ((index < 8) && (result >= thresholds[index]))
    {
        //output = output << 1; 
        //output |= (0b1 << index);
        index++;
    }
    
    //Go down 1 index
    index--;
    
    //Update display
    DISPLAY_setMaxPosition(index);
    //IO_setLEDs(output);
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
    uint8_t result = LTR390_calculateUVIndex();
        
    
#ifdef RESULT_DISPLAY_OUTLINE
    _displayOutline(result, &UV_thresholds[0]);
#else
    _displaySolid(result, &UV_thresholds[0]);
#endif
}

void TEMP_getAndDisplayResults(void)
{
    uint8_t result = MCP9700_measureTemperature();
    
#ifdef RESULT_DISPLAY_OUTLINE
    _displayOutline(result, &TEMP_thresholds[0]);
#else
    _displaySolid(result, &UV_thresholds[0]);
#endif
}

//Display the Heat Index and Update the Display
void HeatIndex_getAndDisplayResults(void)
{
    uint8_t RH = HTU21D_getHumidityMeasurement();
    uint8_t tempC = MCP9700_measureTemperature();
    
    //Convert to F
    uint8_t tempF = ceil((tempC * 1.8) + 32);
    
    uint8_t result;
    
    if (RH == UINT8_MAX)
    {
        //Error!
        return;
    }
    
    if ((RH < 40) || (tempF < 80) || (tempF > 110))
    {
        //Humidity too low, temp too low, or temp too high
        result = tempF;
    }
    else
    {
        //Use lookup table for Heat Index
        
        //Over 100%... (calibration error most likely)
        if (RH > 100)
        {
            RH = 100;
        }
        
        //First, find the row
        //The first row is 40%, and goes by 5% increments
        RH -= 40;
        
        uint8_t row = 0, col = 0;
        
        while (RH >= 5)
        {
            RH -= 5;
            row++;
        }
        
        //Now find the column
        //Starts at 80F, and goes by 2F increments
        
        tempF -= 80;
        while (tempF >= 2)
        {
            tempF -= 2;
            col++;
        }
        
        //Now get the value from memory...
        result = hIndex[row][col];
    }
    
    _displayOutline(result, &TEMP_thresholds[0]);
}

#include "LTR390.h"
#include "LTR390_registers.h"
#include "peripherals/TWI/TWI.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

bool initLTR390(void)
{
    bool ok;
    
#ifdef SW_RESET
    
    //Reset the LTR390
    ok = LTR390_setRegister(MAIN_CTRL, MAIN_CTRL_RST_bm);
    
    //If we failed to send data, exit
    if (!ok)
    {
        return false;
    }
    
    //Wait a few moments - it takes some time for LTR390 to finish it's reset
    for (uint32_t i = 0; i < 100; ++i) { ; }
    
#endif
    
    //18-bit, 100ms Time
    ok = LTR390_setRegister(ALS_UVS_MEAS_RATE, 
            ALS_UVS_MEAS_RESOL_18BIT | ALS_UVS_MEAS_RATE_100MS);
    
    if (!ok)
        return false;
    
    //18x Gain
    ok = LTR390_setRegister(ALS_UVS_GAIN, ALS_UVS_GAIN_18X);
    
    if (!ok)
        return false;
    
    //Enable UV Sensor Mode
    ok = LTR390_setRegister(MAIN_CTRL, MAIN_CTRL_UVS_Mode_bm | MAIN_CTRL_ALS_UVS_EN_bm);
    
    return ok;
}

bool LTR390_setRegister(LTR390_REGISTER reg, uint8_t config)
{
    uint8_t data[2] = {reg, config};
    return TWI_sendBytes(LTR390_ADDR, &data[0], 2);
}

//Set a 24-bit register in the LTR390 
bool LTR390_setRegister24B(LTR390_REGISTER reg, uint8_t upperByte, uint8_t highByte, uint8_t lowByte)
{
    uint8_t data[4] = {reg, upperByte, highByte, lowByte};
    return TWI_sendBytes(LTR390_ADDR, &data[0], 4);
}

//Get a 24-bit register in the LTR390 
bool LTR390_getRegister24B(LTR390_REGISTER reg, uint8_t* value)
{
    return TWI_sendAndReadBytes(LTR390_ADDR, reg, value, 3);
}

uint8_t LTR390_getRegister(LTR390_REGISTER reg)
{
    uint8_t buffer = 0x00;
    TWI_sendAndReadBytes(LTR390_ADDR, reg, &buffer, 1);
    
    return buffer;
}

bool LTR390_isConnected(void)
{
    uint8_t data;
    
    //Get Part ID + Rev Info
    bool ok = TWI_sendAndReadBytes(LTR390_ADDR, PART_ID, &data, 1);
    
    if(!ok)
        return false;
    
    if ((data >> PART_ID_PN_bp) == LTR390_PN_ID)
    {
        //Device ID Match
        return true;
    }
    
    return false;
}

uint8_t calculateUVIndex(void)
{
    uint8_t t_meas[3];
    bool ok = TWI_sendAndReadBytes(LTR390_ADDR, UVS_DATA_0, &t_meas[0], 3);
    
    //If failed, - return bad value
    if (!ok)
        return 0xFF;
    
    //TESTING ONLY
    t_meas[0] = 0x01;
    t_meas[1] = 0x02;
    t_meas[2] = 0x03;
    
    uint32_t meas = ((uint32_t) t_meas[2] << 16) | ((uint16_t) t_meas[1] << 8) | t_meas[0];
    uint8_t result = 0x00;
    
#ifdef WFAC
    //If a Window Factor is defined...
    result = round(((float)(meas / UVI_SENSITIVITY)) * WFAC);
    
#else
    //Window Factor is undefined (assume WFAC = 1.0)
    result = round(meas / UVI_SENSITIVITY);
    
#endif
    return result;
}
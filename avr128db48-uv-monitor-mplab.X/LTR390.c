#include "LTR390.h"
#include "LTR390_registers.h"
#include "peripherals/TWI/TWI.h"

#include <stdint.h>
#include <stdbool.h>

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
    
    //Enable UV Sensor Mode
    ok = LTR390_setRegister(MAIN_CTRL, MAIN_CTRL_UVS_Mode_bm);
    
    return ok;
}

bool LTR390_setRegister(LTR390_REGISTER reg, uint8_t config)
{
    uint8_t data[2] = {reg, config};
    return TWI_sendBytes(LTR390_ADDR, &data[0], 2);
}

uint8_t LTR390_getRegister(LTR390_REGISTER reg)
{
    uint8_t buffer = 0x00;
    TWI_sendAndReadBytes(LTR390_ADDR, reg, &buffer, 1);
    
    return buffer;
}

bool LTR390_isConnected(void)
{
    uint8_t data[1];
       
    bool ok = TWI_sendByte(LTR390_ADDR, PART_ID);   //TWI_sendAndReadBytes(LTR390_ADDR, PART_ID, &data[0], 2);
    
    if (!ok)
    {
        return false;
    }
    
    ok = TWI_readByte(LTR390_ADDR, &data[0]);
    
    if ((data[0] >> PART_ID_PN_bp) == LTR390_PN_ID)
    {
        //Device ID Match
        return true;
    }
    
    return false;
}

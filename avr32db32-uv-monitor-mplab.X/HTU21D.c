#include "HTU21D.h"
#include "TWI0_host.h"

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

//Initialize the HTU21D Sensor
bool HTU21D_init(void)
{
    return HTU21D_writeSettings(0x01);
}

//Sends a command to the sensor
bool HTU21D_sendCommand(HTU21D_COMMAND cmd)
{
    return TWI0_sendByte(HTU21D_ADDR, cmd);
}

//Sends a command to the sensor
bool HTU21D_writeSettings(uint8_t data)
{
    uint8_t data[2] = {HTU21D_WRITE_REG, data};
    return TWI0_sendBytes(HTU21D_ADDR, &data[0], 2);
}

//Writes a command, then reads [len] bytes
bool HTU21D_writeReadRegister(HTU21D_COMMAND cmd, uint8_t* data, uint8_t len)
{
    return TWI0_sendAndReadBytes(HTU21D_ADDR, cmd, &data[0], len);
}

//Starts a temperature measurement, and returns the temperature as a float
float HTU21D_getTempMeasurementFloat(void)
{
    return 0.0;
}

//Starts a temperature measurement, and returns the temperature as an int
int8_t HTU21D_getTempMeasurementInt(void)
{
    return INT8_MIN;
}

//Starts a temperature measurement, and returns the temperature as a float
uint8_t HTU21D_getHumidityMeasurement(void)
{
    uint8_t data[2];
    if (HTU21D_writeReadRegister(HTU21D_HOLD_HUMID, &data[0], 2))
    {
        //Read data from the sensor
        
        //Create 16-bit result (set diag. bits to 0)
        uint16_t measurement = (data[0] << 8) | (data[1] & 0xFC);
        
        //Get Status Bits
        uint8_t status = data[1] & 0x03;
        
        if (measurement == 0x0000)
        {
            //Possible Open Circuit (Sensor Failure)
            if (status == 0b00)
            {
                //Failure
                return UINT8_MAX;
            }
        }
        else if (measurement == 0xFFFF)
        {
            //Possible Short Circuit (Sensor Failure)
            if (status == 0b11)
            {
                //Failure
                return UINT8_MAX;
            }
        }
        
        //Calculate RH
        uint32_t tMeas = measurement;
        tMeas *= 125;
        tMeas = tMeas >> 16;
        
        //If we'd go negative, skip the offset and set to 0
        if (tMeas > 6)
        {
            tMeas += -6;
        }
        else
        {
            tMeas = 0;
        }
        
        return (uint8_t) (tMeas & 0xFF);
    }
    return UINT8_MAX;
}
#ifndef HTU21D_H
#define	HTU21D_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
    
/* API for HTU21D(F) Series Sensors by TE Connectivity */

    typedef enum{
        HTU21D_HOLD_TEMP = 0xE3, HTU21D_HOLD_HUMID = 0xE5, HTU21D_NO_HOLD_TEMP = 0xF3, 
                HTU21D_NO_HOLD_HUMID = 0xF5, HTU21D_WRITE_REG = 0xE6, HTU21D_READ_REG = 0xE7, HTU21D_RESET_CMD = 0xFE
    } HTU21D_COMMAND;

#define HTU21D_ADDR 0x40
    
    //Initialize the HTU21D Sensor
    bool HTU21D_init(void);
    
    //Sends a command to the sensor
    bool HTU21D_sendCommand(HTU21D_COMMAND cmd);
    
    //Write the settings on the HTU21D
    bool HTU21D_writeSettings(uint8_t data);

    //Writes a command, then reads [len] bytes
    bool HTU21D_writeReadRegister(HTU21D_COMMAND cmd, uint8_t* data, uint8_t len); 
    
    //Starts a temperature measurement, and returns the temperature as a float
    float HTU21D_getTempMeasurementFloat(void);
    
    //Starts a temperature measurement, and returns the temperature as an int
    int8_t HTU21D_getTempMeasurementInt(void);
    
    //Starts a temperature measurement, and returns the temperature as an int
    uint8_t HTU21D_getHumidityMeasurement(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HTU21D_H */


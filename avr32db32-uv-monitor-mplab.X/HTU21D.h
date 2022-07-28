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
    
//Battery Status
#define HTU21D_STATUS_bp 6
#define HTU21D_STATUS_bm (0b1 << HTU21D_STATUS_bp)
    
//Reserved Bits
#define HTU21D_RESERVED_bp 3
#define HTU21D_RESERVED_bm (0b111 << HTU21D_RESERVED_bp)
    
//On-Chip Heater
#define HTU21D_HEATER_EN_bp 2
#define HTU21D_HEATER_EN_bm (0b01 << HTU21D_HEATER_EN_bp)
    
//OTP Reload
#define HTU21D_OTP_RELOAD_DISABLE_bp 1
#define HTU21D_OTP_RELOAD_DISABLE_bm (0b1 << HTU21D_OTP_RELOAD_bp)
    
//Measurement Resolution
#define HTU21D_RES_RH_TEMP_gp 0
#define HTU21D_RES_12_RH_14_TEMP_gm (0x00 << HTU21D_RES_RH_TEMP_gp)
#define HTU21D_RES_8_RH_12_TEMP_gm  (0x01 << HTU21D_RES_RH_TEMP_gp)
#define HTU21D_RES_10_RH_13_TEMP_gm (0x80 << HTU21D_RES_RH_TEMP_gp)
#define HTU21D_RES_11_RH_11_TEMP_gm (0x81 << HTU21D_RES_RH_TEMP_gp)
    
    
//I2C Address for Sensor
#define HTU21D_ADDR 0x40
    
    //Initialize the HTU21D Sensor
    bool HTU21D_init(void);
    
    //Sends a command to the sensor
    bool HTU21D_sendCommand(HTU21D_COMMAND cmd);
    
    //Write the settings on the HTU21D
    bool HTU21D_writeSettings(uint8_t setting);

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


#ifndef LTR390_REGISTERS_H
#define	LTR390_REGISTERS_H

#ifdef	__cplusplus
extern "C" {
#endif

//I2C Base Address of Sensor
#define LTR390_ADDR 0x53
    
//Internal Part Number ID
#define LTR390_PN_ID 0b1011
    
    typedef enum {
                MAIN_CTRL = 0x00, 
                ALS_UVS_MEAS_RATE = 0x04, ALS_UVS_GAIN, PART_ID, MAIN_STATUS,
                ALS_DATA_0 = 0x0D, ALS_DATA_1, ALS_DATA_2, 
                UVS_DATA_0, UVS_DATA_1, UVS_DATA_2, 
                INT_CFG = 0x19, 
                INT_PST = 0x1A, 
                ALS_UVS_THRES_UP_0 = 0x21, ALS_UVS_THRES_UP_1, ALS_UVS_THRES_UP_2,
                ALS_UVS_THRES_LOW_0, ALS_UVS_THRES_LOW_1, ALS_UVS_THRES_LOW_2
    } LTR390_REGISTER;
    
//Main Control
#define MAIN_CTRL_RST_bp            4
#define MAIN_CTRL_RST_bm            (0b1 << MAIN_CTRL_RST_bp)
    
#define MAIN_CTRL_UVS_Mode_bp       3
#define MAIN_CTRL_UVS_Mode_bm       (0b1 << MAIN_CTRL_UVS_Mode_bp)
    
#define MAIN_CTRL_ALS_UVS_EN_bp     1
#define MAIN_CTRL_ALS_UVS_EN_bm     (0b1 << MAIN_CTRL_ALS_UVS_EN_bp)
    
//Ambient Light / UV Sensor Measurement
    
#define ALS_UVS_MEAS_RESOL_20BIT    0b000   //400ms min
#define ALS_UVS_MEAS_RESOL_19BIT    0b001   //200ms min
#define ALS_UVS_MEAS_RESOL_18BIT    0b010   //100ms min
#define ALS_UVS_MEAS_RESOL_17BIT    0b011   //50ms min
#define ALS_UVS_MEAS_RESOL_16BIT    0b100   //25ms min
#define ALS_UVS_MEAS_RESOL_13BIT    0b101   //12.5ms min
    
#define ALS_UVS_MEAS_RESOL_gp       4
#define ALS_UVS_MEAS_RESOL_gm       (0b111 << ALS_UVS_MEAS_RESOL_gp)
    
#define ALS_UVS_MEAS_RATE_25MS      0b000 
#define ALS_UVS_MEAS_RATE_50MS      0b001
#define ALS_UVS_MEAS_RATE_100MS     0b010
#define ALS_UVS_MEAS_RATE_200MS     0b011
#define ALS_UVS_MEAS_RATE_500MS     0b100
#define ALS_UVS_MEAS_RATE_1000MS    0b101
#define ALS_UVS_MEAS_RATE_2000MS    0b110   //Also valid - 0b111
  
#define ALS_UVS_MEAS_RATE_gp        0
#define ALS_UVS_MEAS_RATE_gm        (0b111 << ALS_UVS_MEAS_RATE_gp)
    
//Ambient Light / UV Sensor Gain
#define ALS_UVS_GAIN_1X             0b000
#define ALS_UVS_GAIN_3X             0b001
#define ALS_UVS_GAIN_6X             0b010
#define ALS_UVS_GAIN_9X             0b011
#define ALS_UVS_GAIN_18X            0b100

#define ALS_UVS_GAIN_gp 0
    
//Part ID
#define PART_ID_PN_bm               0xF0
#define PART_ID_REV_ID_bm           0x0F
    
#define PART_ID_PN_bp               4
#define PART_ID_REV_ID_bp           0
    
//Main Status
#define MAIN_STATUS_PWR_ON_bp       5
#define MAIN_STATUS_PWR_ON_bm       (0b1 << MAIN_STATUS_PWR_ON_bp)
    
#define MAIN_STATUS_INT_STATUS_bp   4
#define MAIN_STATUS_INT_STATUS_bm   (0b1 << MAIN_STATUS_INT_STATUS_bp)

#define MAIN_STATUS_DATA_STATUS_bp  3
#define MAIN_STATUS_DATA_STATUS_bm  (0b1 << MAIN_STATUS_DATA_STATUS_bp)

//Ambient Light Data
#define ALS_DATA_gm                 0x0FFFFF
    
//UV Light Data
#define UVS_DATA_gm                 0x0FFFFF
    
//INT Configuration
#define INT_CFG_INT_ALS             0b01
#define INT_CFG_INT_UVS             0b11
    
#define INT_CFG_INT_SRC_gp          4
#define INT_CFG_INT_SRC_gm          (0b11 << INT_CFG_INT_SRC_gp)
    
#define INT_CFG_ENABLE_bp           2
#define INT_CFG_ENABLE_bm           (0b1 << INT_CFG_ENABLE_bp)
    
//INT Persist Configuration
#define INT_PST_1X                  0b0000
#define INT_PST_2X                  0b0001
#define INT_PST_3X                  0b0010
#define INT_PST_4X                  0b0011
#define INT_PST_5X                  0b0100
#define INT_PST_6X                  0b0101
#define INT_PST_7X                  0b0110
#define INT_PST_8X                  0b0111
#define INT_PST_9X                  0b1000
#define INT_PST_10X                 0b1001
#define INT_PST_11X                 0b1010
#define INT_PST_12X                 0b1011
#define INT_PST_13X                 0b1100
#define INT_PST_14X                 0b1101
#define INT_PST_15X                 0b1110
#define INT_PST_16X                 0b1111

#define INT_PST_gp                  4
#define INT_PST_gm                  (0b1111 << INT_PST_gp)
    
//Ambient Light / UV Light Thresholds (Both Low and High)
#define ALS_UVS_THRES_gm            (0x0FFFFF)

#ifdef	__cplusplus
}
#endif

#endif	/* LTR390_REGISTERS_H */


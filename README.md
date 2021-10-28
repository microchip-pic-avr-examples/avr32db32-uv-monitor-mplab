<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# Batteryless UV Index (UVI) and Temperature Monitor with AVR128DB28
This demo of the AVR DB family of MCUs implements a batteryless solar energy harvester to measure either the UV Index or the ambient temperature.

## Related Documentation

## Software Used
- [MPLAB X IDE v5.50.0 or newer](#)
- [MPLAB XC8 v2.32 or newer](#)

## Hardware Used
- AVR128DB28
- LTR390UV Sensor (or breakout from Adafruit)
- MCP9700 Analog Temperature Sensor

## Setup
| Pin(s) | Function
| ------ | ---------
| PA0:7  | LED Bar Graph Display Output
| PC0    | UART TX (3.3V)
| PC1    | UART RX (3.3V)
| PC2    | I2C SDA (3.3V)
| PC3    | I2C SCL (3.3V)
| PD1    | Measurement Active LED
| PD2    | Boost Converter PWM Out
| PD3    | Boost Converter Analog Feedback
| PD5    | Analog Temperature Output from MCP9700
| PD6    | Start UV Measurement Button
| PD7    | Start Temperature Measurement Button
| PF0    | (Debug Only) TCD-A PWM Output
| PF1    | LED Drive PWM

### Voltage Levels
AVR DB Supply: 5V  
AVR DB MVIO Supply: 3.3V

## Implementation
**Warning: This demo is for educational use only. Please obtain accurate UV Index and Temperature measurements from a trusted source, such as the [National Oceanic and Atmospheric Administration (noaa.gov)](noaa.gov). Prolonged exposure to high temperatures can be life-threatening.**

### Overview
The heart of this program is an event driven state machine with the following states:
```
typedef enum {
    SYSTEM_NONE = 0x00, UV_MEAS, TEMP_MEAS, WAIT_UV, WAIT_TEMP, TIMER_UV, TIMER_TEMP
} SYSTEM_EVENT;
 ```  

After initialization, the system starts in the `SYSTEM_NONE` state. This state puts the device into sleep mode. There are 2 ways to exit sleep mode in this program. The first is the Periodic Interrupt Timer (PIT) that approximately triggers every 250 ms. The PIT is used to periodically check and adjust (if necessary) the duty cycle of the boost converter. The second interrupt is from a falling edge on the pushbuttons. If a pushbutton is pressed, then the state machine will jump to `UV_MEAS` or `TEMP_MEAS`, depending on which button was pressed. To prevent re-triggering, I/O interrupts are also disabled. (They are re-enabled before sleep in the `SYSTEM_NONE` state).

//TODO: State Diagram

### Solar Energy Harvester
To generate the 5V supply for this demo, a simple boost converter was built using the Core Independent Peripherals (CIPs) on AVR DB. To run the boost, a 100 kHz PWM was created in the Timer/Counter D (TCD) peripheral on the device. The TCD output is then gated by the Analog Comparator (AC) via the logical AND inside of the Configurable Custom Logic (CCL). This configuration is shown below.

//TODO: Add Figure

This creates a regulating boost converter, but it does not correct for changing load conditions. To determine how loaded the regulator is, the number of output pulses is counted by TCB for a fixed number of generated TCD pulses (before the logic AND). This effectively creates a time delay of `PULSE_WAIT` (default: 1000 pulses, or 10 ms) to gather data.

If the number of *skipped* pulses is 0, then the duty cycle needs to be increased by 1, up to `MAX_DUTY_CYCLE` (default: 20 cycles of TCD, or 50%).

If the number of *output* pulses is greater than `DC_REDUCE_THRESHOLD` (default: 90% of `PULSE_WAIT`), then the duty cycle needs to be decreased by 1, down to `MIN_DUTY_CYCLE` (default: 1 cycle of TCD, or 2.5%). **Note: `DC_REDUCE_THRESHOLD` uses the number of OUTPUT pulses, not skipped pulses.**

If neither of these conditions occur, then the duty cycle is maintained with no changes.

### UV Index Monitor
For each measurement of the UV Index, there are 3 program states, as shown below:

UV_MEAS &rarr; WAIT_UV &rarr; TIMER_UV  

The `UV_MEAS` state is the state where the result stored in the UV Sensor is retrieved, and the UV Index is calculated. The program updates the LED bar graph display with the following scale:

//TODO: Show Scale

After updating the display, the program switches to the `WAIT_UV` state. The program remains in this state until the PIT occurs `PIT_WAIT` (default: 4) times. This ensures the sensor has new measurement data. From `WAIT_UV` the state machine goes to `TIMER_UV`. The `TIMER_UV` state counts the number of measurements performed since sleep. When the count is equal to `SAMPLES_UV` (default: 20), then the program is switched to the `SYSTEM_NONE` state.

### Temperature Monitor
For each temperature measurement, there are 3 program states, as shown below.

TEMP_MEAS &rarr; WAIT_TEMP &rarr; TIMER_TEMP

The `TEMP_MEAS` state is when the analog output is measured by the ADC. The analog output is converted to the equivalent temperature, then used to update the bar graph display.

//TODO: Show Scale

 The state machine then switches to the `WAIT_TEMP` state. This state is used to prevent the display from flickering from excessive updates. When the next PIT interrupt occurs, the state is moved to `TIMER_TEMP`. The `TIMER_TEMP` state keeps track of the number of temperature measurements since sleep. When the count is equal to `SAMPLES_TEMP` (default: 20), then the program returns to the `SYSTEM_NONE` state.

### LED Dimming
To save power, the LEDs on the board are dimmed with PWM. Since the TCD is already generating a 100 kHz signal for the boost converter, the channel B of the TCD is reused as a PWM output for the LEDs with a duty cycle of 25%. The LEDs are turned on using the I/O in an active-LOW configuration.

## Testing

## Operating this Example


## Other Notes

## Summary

<!-- Summarize what the example has shown -->

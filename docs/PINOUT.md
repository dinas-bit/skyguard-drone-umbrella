# SkyGuard ESP32-S3 Pinout

## GPIO Assignments

| GPIO | Function | Peripheral | Notes |
|------|----------|------------|-------|
| 2 | LED | Digital Out | Status LED |
| 12 | Motor FL | PWM/DShot | Front-Left ESC signal |
| 13 | Motor FR | PWM/DShot | Front-Right ESC signal |
| 14 | Motor BL | PWM/DShot | Back-Left ESC signal |
| 15 | Motor BR | PWM/DShot | Back-Right ESC signal |
| 16 | GPS RX | UART2 | NEO-M8N TX -> ESP RX |
| 17 | GPS TX | UART2 | NEO-M8N RX -> ESP TX |
| 18 | Camera SCK | SPI | OV2640 SPI clock |
| 19 | Camera MISO | SPI | OV2640 SPI data out |
| 21 | I2C SDA | I2C | DW1000 UWB data |
| 22 | I2C SCL | I2C | DW1000 UWB clock |
| 23 | Camera MOSI | SPI | OV2640 SPI data in |
| 34 | Rain Sensor | ADC | DHT22 analog out |
| 35 | Battery | ADC | Voltage divider |

## Wiring Diagram (ASCII)

```
                    +---------+
     GPS TX ----> 16|         |
     GPS RX <--- 17|         |
    Rain ADC <--- 34|  ESP32  |
    Batt ADC <--- 35|   S3    |
    I2C SDA <-> 21|         |
    I2C SCL <-> 22|         |
     LED <------ 2|         |
                    +---------+
                         |
           +------+------+------+------+
           |      |      |      |      |
         GPIO12 GPIO13 GPIO14 GPIO15
           |      |      |      |
          ESC1   ESC2   ESC3   ESC4
           |      |      |      |
          M_FL   M_FR   M_BL   M_BR
```

# SkyGuard Hardware Guide

## Bill of Materials

| Component | Model | Cost |
|-----------|-------|------|
| Flight Controller | SpeedyBee F405 | $35 |
| Motors (x4) | T-Motor F80 Pro | $60 |
| ESC | 4-in-1 BLHeli_32 | $40 |
| GPS | u-blox NEO-M8N | $12 |
| UWB | DW1000 | $18 |
| Camera | ESP32-CAM | $8 |
| Rain Sensor | DHT22 | $3 |
| Battery | 4S 3000mAh | $35 |
| Frame | DJI F450 | $15 |
| Total | | $226 |

## Wiring

ESP32-S3 -> UART2 (GPS) -> I2C (UWB) -> SPI (Camera) -> ADC (Rain) -> PWM (ESC)

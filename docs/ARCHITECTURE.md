# SkyGuard Architecture

## System Overview

```
Application Layer: Follow-me | Hover | Failsafe | Rain
Control Layer: PID Controller | Motor Mixer
Perception Layer: GPS Fusion | CV Detection | UWB
Hardware Abstraction: UART | I2C | SPI | ADC | PWM
```

## Data Flow

1. Sensor Fusion: GPS + UWB via Kalman filter
2. Person Detection: Camera -> YOLO-nano -> bounding box
3. Position Calculation: Offset from target
4. PID Control: Error -> PID -> motor commands
5. Motor Mixing: X-configuration quadcopter

## Safety Systems

- GPS Loss: Auto-land immediately
- Battery < 20%: Return to home
- Battery < 10%: Emergency land
- RC Kill Switch: Immediate stop

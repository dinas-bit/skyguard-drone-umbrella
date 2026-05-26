# SkyGuard - Smart Umbrella Drone

A next-gen drone that follows you automatically, keeping you dry in the rain — hands-free!

## What is SkyGuard?

SkyGuard is a consumer drone concept that combines GPS tracking, computer vision, and autonomous flight to serve as your personal flying umbrella. It detects when it's raining, locks onto your position, and hovers above you to shield you from rain.

## Key Features

- **GPS + UWB Positioning** — Centimeter-accuracy tracking so it stays directly above you
- **Computer Vision** — Real-time person detection using lightweight neural networks (YOLO nano)
- **Autonomous Follow-Me** — Smooth trajectory planning with PID control for stable hover
- **Auto-Deploy** — Activates when rain is detected via onboard hygrometer sensor
- **Failsafe Return** — Returns to home base if battery drops below 20%
- **Modular Umbrella Attachment** — Quick-release mount for different umbrella sizes

## Tech Stack

- **MCU:** ESP32-S3 (WiFi + BLE + camera interface)
- **Flight Controller:** Betaflight-compatible with DShot600 ESC protocol
- **Navigation:** u-blox NEO-M8N GPS + DW1000 UWB ranging
- **Vision:** OV2640 camera + TFLite micro inference
- **Communication:** MAVLink over WiFi
- **Simulation:** Gazebo + ROS2 Humble for development & testing

## Project Structure

```
skyguard-drone-umbrella/
├── firmware/              # ESP32 firmware (Arduino/PlatformIO)
│   ├── src/
│   │   ├── main.cpp
│   │   ├── gps_tracker.h
│   │   ├── pid_controller.h
│   │   ├── person_detector.h
│   │   ├── rain_sensor.h
│   │   └── failsafe.h
│   └── platformio.ini
├── simulation/            # Gazebo + ROS2 simulation
│   ├── launch/
│   ├── worlds/
│   └── models/
├── vision/                # CV models & training
│   ├── train_person_detection.py
│   └── export_tflite.py
├── docs/                  # Architecture & diagrams
│   ├── ARCHITECTURE.md
│   └── HARDWARE.md
└── README.md
```

## Quick Start

### Firmware (ESP32)

```bash
cd firmware
# Install PlatformIO CLI
pip install platformio

# Build and flash
pio run -t upload
```

### Simulation (ROS2)

```bash
# Terminal 1: Start Gazebo world
cd simulation
ros2 launch skyguard_sim world.launch.py

# Terminal 2: Run follow-me controller
ros2 run skyguard_controller follow_me_node
```

## How It Works

1. **Rain Detection** — Onboard DHT22 sensor detects humidity spike (>80% RH)
2. **Target Acquisition** — Camera scans for human silhouette, locks centroid
3. **GPS + UWB Fusion** — Kalman filter combines both for precise positioning
4. **PID Hover Control** — Maintains 2.5m altitude, directly above target
5. **Continuous Tracking** — Re-detects every 500ms, adjusts trajectory smoothly
6. **Failsafe** — Low battery triggers auto-land or return-to-home

## Hardware Bill of Materials

| Component | Model | Est. Cost |
|-----------|-------|-----------|
| Flight Controller | SpeedyBee F405 | $35 |
| Motors | T-Motor F80 Pro (x4) | $60 |
| ESC | 4-in-1 BLHeli_32 45A | $40 |
| GPS | u-blox NEO-M8N | $12 |
| UWB | DW1000 Module | $18 |
| Camera | ESP32-CAM (OV2640) | $8 |
| Rain Sensor | DHT22 | $3 |
| Battery | 4S 3000mAh LiPo | $35 |
| Frame | DJI F450 clone | $15 |
| Umbrella Mount | 3D printed PETG | $5 |

**Total BOM: ~$231**

## Safety Notes

- Max takeoff weight under 250g (sub-250g category)
- Visual line of sight required in most jurisdictions
- Auto-lands if GPS lock is lost
- Emergency kill-switch on RC transmitter
- Complies with FAA Part 107 for recreational use

## Contributing

1. Fork the repo
2. Create a feature branch (`git checkout -b feat/amazing-feature`)
3. Commit your changes
4. Push to the branch and open a PR

## License

MIT License — see [LICENSE](LICENSE) for details.# skyguard-drone-umbrella
Smart drone umbrella that follows you automatically using GPS tracking and computer vision. Stay dry hands-free!

# Changelog

All notable changes to SkyGuard will be documented in this file.

## [0.3.0] - 2026-05-26

### Added
- ESP32-S3 firmware with full flight control
- GPS + UWB sensor fusion via Kalman filter
- YOLO-nano person detection on ESP32-CAM
- DHT22 rain sensor integration
- PID altitude and position control
- Failsafe system (battery, GPS loss, RC loss)
- Gazebo + ROS2 simulation environment
- URDF drone model with propeller animation
- CI/CD pipeline via GitHub Actions
- Docker support for simulation
- Unit tests for vision module
- Comprehensive hardware documentation

### Changed
- Upgraded PID controller with anti-windup
- Improved GPS parsing reliability

## [0.2.0] - 2026-05-20

### Added
- Person detection model (MobileNetV3-Small)
- TFLite export pipeline
- Basic simulation environment

## [0.1.0] - 2026-05-15

### Added
- Initial project structure
- README and architecture docs
- Hardware BOM research

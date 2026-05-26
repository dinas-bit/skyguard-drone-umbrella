#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "gps_tracker.h"
#include "pid_controller.h"
#include "person_detector.h"
#include "rain_sensor.h"
#include "failsafe.h"

#define LED_PIN 2
#define BATTERY_PIN 35
#define MOTOR_FL 12
#define MOTOR_FR 13
#define MOTOR_BL 14
#define MOTOR_BR 15

GPSTracker gps;
PIDController pid(2.0, 0.5, 0.1);
PersonDetector detector;
RainSensor rainSensor;
Failsafe failsafe;

float targetLat = 0.0, targetLon = 0.0;
float currentAlt = 2.5;
bool isFollowing = false;
bool rainDetected = false;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    pinMode(LED_PIN, OUTPUT);
    pinMode(BATTERY_PIN, INPUT);
    gps.begin();
    pid.begin();
    detector.begin();
    rainSensor.begin();
    failsafe.begin(BATTERY_PIN);
    digitalWrite(LED_PIN, HIGH);
    Serial.println("[SkyGuard] System initialized");
}

void loop() {
    rainDetected = rainSensor.isRaining();
    if (rainDetected && !isFollowing) {
        Serial.println("[SkyGuard] Rain detected! Activating follow-me...");
        isFollowing = true;
    }
    if (!rainDetected && isFollowing) {
        Serial.println("[SkyGuard] Rain stopped. Landing...");
        isFollowing = false;
        land();
    }
    if (failsafe.shouldLand()) {
        Serial.println("[SkyGuard] Failsafe triggered! Battery low.");
        isFollowing = false;
        emergencyLand();
    }
    if (isFollowing) {
        if (gps.hasFix()) {
            targetLat = gps.getLatitude();
            targetLon = gps.getLongitude();
        }
        if (detector.personDetected()) {
            float offsetX = detector.getOffsetX();
            float offsetY = detector.getOffsetY();
            pid.adjustPosition(offsetX, offsetY);
        }
        float throttle = pid.compute(currentAlt);
        setMotors(throttle);
    }
    delay(10);
}

void setMotors(float throttle) {
    int pwm = map(throttle * 100, 0, 100, 1000, 2000);
    pwm = constrain(pwm, 1000, 2000);
    analogWrite(MOTOR_FL, pwm);
    analogWrite(MOTOR_FR, pwm);
    analogWrite(MOTOR_BL, pwm);
    analogWrite(MOTOR_BR, pwm);
}

void land() {
    for (int alt = 100; alt > 0; alt--) {
        float pwm = map(alt, 100, 0, 1600, 1000);
        setMotors(pwm / 1000.0);
        delay(50);
    }
    setMotors(0);
}

void emergencyLand() {
    for (int i = 100; i > 0; i--) {
        float pwm = i / 100.0;
        setMotors(pwm);
        delay(30);
    }
    setMotors(0);
}

#ifndef PERSON_DETECTOR_H
#define PERSON_DETECTOR_H
#include <Arduino.h>

class PersonDetector {
private:
    float offsetX, offsetY;
    bool detected;
    unsigned long lastDetection;
public:
    PersonDetector() : offsetX(0), offsetY(0), detected(false), lastDetection(0) {}
    void begin() { Serial.println("[Detector] Initialized"); }
    bool personDetected() {
        if (millis() - lastDetection < 500) return detected;
        lastDetection = millis();
        detected = true; offsetX = 0; offsetY = 0;
        return detected;
    }
    float getOffsetX() { return offsetX; }
    float getOffsetY() { return offsetY; }
};
#endif

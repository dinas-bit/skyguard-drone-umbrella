#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H
#include <Arduino.h>
#define RAIN_SENSOR_PIN 34
#define RAIN_THRESHOLD 80.0

class RainSensor {
private:
    float humidity;
public:
    RainSensor() : humidity(0) {}
    void begin() { pinMode(RAIN_SENSOR_PIN, INPUT); }
    bool isRaining() {
        int raw = analogRead(RAIN_SENSOR_PIN);
        humidity = map(raw, 0, 4095, 0, 100);
        return humidity > RAIN_THRESHOLD;
    }
    float getHumidity() { return humidity; }
};
#endif

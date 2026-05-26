#ifndef FAILSAFE_H
#define FAILSAFE_H
#include <Arduino.h>
#define BATTERY_LOW 3.5
#define NUM_CELLS 4

class Failsafe {
private:
    int batteryPin;
    float voltage, cellVoltage;
public:
    Failsafe() : batteryPin(0), voltage(0), cellVoltage(0) {}
    void begin(int pin) { batteryPin = pin; analogReadResolution(12); }
    bool shouldLand() {
        int raw = analogRead(batteryPin);
        voltage = (raw / 4095.0) * 3.3 * 5.5;
        cellVoltage = voltage / NUM_CELLS;
        return cellVoltage < BATTERY_LOW;
    }
    float getVoltage() { return voltage; }
};
#endif

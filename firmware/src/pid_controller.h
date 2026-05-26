#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include <Arduino.h>

class PIDController {
private:
    float kp, ki, kd;
    float integralX, prevErrorX;
    unsigned long prevTime;
public:
    PIDController(float p, float i, float d) : kp(p), ki(i), kd(d), integralX(0), prevErrorX(0), prevTime(0) {}
    void begin() { prevTime = millis(); }
    float compute(float currentAlt) {
        unsigned long now = millis();
        float dt = (now - prevTime) / 1000.0;
        prevTime = now;
        float error = 2.5 - currentAlt;
        integralX += error * dt;
        integralX = constrain(integralX, -5.0, 5.0);
        float derivative = (error - prevErrorX) / dt;
        prevErrorX = error;
        return constrain(kp * error + ki * integralX + kd * derivative, 0.0, 1.0);
    }
    void adjustPosition(float offX, float offY) {
        unsigned long now = millis();
        float dt = (now - prevTime) / 1000.0;
        integralX += offX * dt;
        integralX = constrain(integralX, -2.0, 2.0);
        prevErrorX = offX;
    }
};
#endif

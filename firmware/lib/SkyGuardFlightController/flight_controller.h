#ifndef FLIGHT_CONTROLLER_H
#define FLIGHT_CONTROLLER_H

#include <Arduino.h>

struct MotorOutput {
    float fl, fr, bl, br;
};

struct Attitude {
    float roll, pitch, yaw;
};

struct Position {
    float x, y, z;
};

class FlightController {
private:
    Attitude attitude;
    Position position;
    Position target;
    float hoverThrottle;
    
    // PID state for each axis
    struct PIDState {
        float integral;
        float prevError;
        unsigned long prevTime;
    };
    
    PIDState rollPID, pitchPID, yawPID, altPID;
    float rollKP, rollKI, rollKD;
    float pitchKP, pitchKI, pitchKD;
    float yawKP, yawKI, yawKD;
    float altKP, altKI, altKD;
    
public:
    FlightController() : hoverThrottle(0.5f) {
        attitude = {0, 0, 0};
        position = {0, 0, 2.5f};
        target = {0, 0, 2.5f};
        rollPID = pitchPID = yawPID = altPID = {0, 0, 0};
        rollKP = 1.5f; rollKI = 0.1f; rollKD = 0.05f;
        pitchKP = 1.5f; pitchKI = 0.1f; pitchKD = 0.05f;
        yawKP = 2.0f; yawKI = 0.0f; yawKD = 0.1f;
        altKP = 2.0f; altKI = 0.5f; altKD = 0.1f;
    }
    
    void setTarget(float x, float y, float z) {
        target = {x, y, z};
    }
    
    void updateAttitude(float roll, float pitch, float yaw) {
        attitude = {roll, pitch, yaw};
    }
    
    void updatePosition(float x, float y, float z) {
        position = {x, y, z};
    }
    
    MotorOutput compute() {
        unsigned long now = micros();
        float dt = (now - altPID.prevTime) / 1000000.0f;
        if (dt <= 0) dt = 0.001f;
        altPID.prevTime = now;
        
        // Altitude PID
        float altError = target.z - position.z;
        altPID.integral += altError * dt;
        altPID.integral = constrain(altPID.integral, -2.0f, 2.0f);
        float altDeriv = (altError - altPID.prevError) / dt;
        altPID.prevError = altError;
        
        float throttle = hoverThrottle + 
            altKP * altError + altKI * altPID.integral + altKD * altDeriv;
        throttle = constrain(throttle, 0.0f, 1.0f);
        
        // Position PID -> attitude commands
        float posXError = target.x - position.x;
        float posYError = target.y - position.y;
        
        float rollCmd = constrain(posXError * 0.5f, -0.3f, 0.3f);
        float pitchCmd = constrain(posYError * 0.5f, -0.3f, 0.3f);
        
        // Motor mixing (X configuration)
        MotorOutput out;
        out.fl = throttle + rollCmd - pitchCmd;
        out.fr = throttle - rollCmd - pitchCmd;
        out.bl = throttle + rollCmd + pitchCmd;
        out.br = throttle - rollCmd + pitchCmd;
        
        out.fl = constrain(out.fl, 0.0f, 1.0f);
        out.fr = constrain(out.fr, 0.0f, 1.0f);
        out.bl = constrain(out.bl, 0.0f, 1.0f);
        out.br = constrain(out.br, 0.0f, 1.0f);
        
        return out;
    }
    
    void reset() {
        rollPID = pitchPID = yawPID = altPID = {0, 0, 0};
    }
};

#endif

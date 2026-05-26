#!/usr/bin/env python3
"""Hardware test script for SkyGuard components.

Run this on the ESP32 to verify all sensors and motors are working.
Connect via: screen /dev/ttyUSB0 115200
"""

import serial
import sys
import time


def test_serial(port="/dev/ttyUSB0", baud=115200):
    """Test serial connection to ESP32."""
    try:
        ser = serial.Serial(port, baud, timeout=2)
        print(f"[OK] Serial connected on {port}")
        
        # Send test command
        ser.write(b"TEST\n")
        time.sleep(1)
        response = ser.readline().decode().strip()
        
        if "OK" in response:
            print(f"[OK] ESP32 responded: {response}")
            return True
        else:
            print(f"[WARN] Unexpected response: {response}")
            return False
    except Exception as e:
        print(f"[FAIL] Serial error: {e}")
        return False


def test_gps(port="/dev/ttyUSB0"):
    """Verify GPS fix acquisition."""
    ser = serial.Serial(port, 115200, timeout=5)
    ser.write(b"GPS_STATUS\n")
    time.sleep(2)
    resp = ser.readline().decode().strip()
    
    if "FIX" in resp:
        print(f"[OK] GPS has fix")
        return True
    else:
        print(f"[WARN] No GPS fix yet: {resp}")
        return False


def test_motors(port="/dev/ttyUSB0"):
    """Spin motors at low throttle to verify ESC connections."""
    ser = serial.Serial(port, 115200, timeout=2)
    print("[INFO] Spinning motors at 10% throttle for 2 seconds...")
    
    ser.write(b"MOTOR_TEST 100\n")
    time.sleep(2)
    ser.write(b"MOTOR_STOP\n")
    
    print("[OK] Motor test complete")
    return True


def test_sensors(port="/dev/ttyUSB0"):
    """Read all sensor values."""
    ser = serial.Serial(port, 115200, timeout=2)
    ser.write(b"SENSOR_DUMP\n")
    time.sleep(1)
    
    while ser.in_waiting:
        line = ser.readline().decode().strip()
        print(f"  {line}")
    
    return True


if __name__ == "__main__":
    port = sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB0"
    
    print("=== SkyGuard Hardware Test ===")
    print(f"Port: {port}")
    print()
    
    tests = [
        ("Serial", lambda: test_serial(port)),
        ("GPS", lambda: test_gps(port)),
        ("Sensors", lambda: test_sensors(port)),
        ("Motors", lambda: test_motors(port)),
    ]
    
    passed = 0
    for name, test_fn in tests:
        print(f"--- {name} ---")
        if test_fn():
            passed += 1
        print()
    
    print(f"=== Results: {passed}/{len(tests)} passed ===")

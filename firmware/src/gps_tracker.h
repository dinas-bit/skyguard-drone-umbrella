#ifndef GPS_TRACKER_H
#define GPS_TRACKER_H
#include <Arduino.h>
#include <HardwareSerial.h>
#define GPS_RX 16
#define GPS_TX 17
#define GPS_BAUD 9600

class GPSTracker {
private:
    HardwareSerial gpsSerial;
    float latitude, longitude;
    bool fix;
public:
    GPSTracker() : gpsSerial(2), latitude(0), longitude(0), fix(false) {}
    void begin() { gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX, GPS_TX); }
    bool hasFix() {
        while (gpsSerial.available()) {
            String sentence = gpsSerial.readStringUntil(chr(10));
            if (sentence.startsWith("$GPGGA")) parseGGA(sentence);
        }
        return fix;
    }
    float getLatitude() { return latitude; }
    float getLongitude() { return longitude; }
private:
    void parseGGA(String sentence) {
        int commaCount = 0, lastComma = 0;
        String fields[15];
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] == ',') { fields[commaCount] = sentence.substring(lastComma, i); lastComma = i + 1; commaCount++; }
        }
        fields[commaCount] = sentence.substring(lastComma);
        if (commaCount >= 6) {
            fix = (fields[6] == "1" || fields[6] == "2");
            if (fix && fields[2].length() > 0) { latitude = fields[2].toFloat(); longitude = fields[4].toFloat(); }
        }
    }
};
#endif

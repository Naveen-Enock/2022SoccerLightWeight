#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
class CompassSensor {

    public: 
        CompassSensor();
        int getOrientation();


    private:
    void displayCalStatus(void);
    Adafruit_BNO055 bno;
    sensors_event_t event;
    void displaySensorDetails();
    void displaySensorStatus();
};
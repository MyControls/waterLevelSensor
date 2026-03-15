#include "Arduino.h"
#include "LevelSensorApp.h"


int adcMode = ADC_VDD;
ADC_MODE(adcMode);


LevelSensorApp app;


void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("Los !");
    //
    app.setup();
    app.enapleSleeping(true);

}


void loop() {
    app.loop();
}

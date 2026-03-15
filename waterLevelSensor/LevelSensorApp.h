/*
 * SensorApp.h
 *
 *  Created on: 09.04.2024
 *      Author: EliteBook HP840
 */
#include "Arduino.h"
#include "WiFiEndPoint.h"

#ifndef SENSORAPP_H_
#define SENSORAPP_H_

class LevelSensorApp : public WiFiEndPoint
    {


 protected:
        int level1;
        int level2;
        String strLevel1;
        String strLevel2;

	void loadSensors();
	void generateXML();
	void insertSensorDataToHtml(WiFiClient &request);
	void sendResponse(WiFiClient &request);

public:
    LevelSensorApp();
    };

#endif /* SENSORAPP_H_ */

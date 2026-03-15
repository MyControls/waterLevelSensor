/*
 * SensorApp.cpp
 *
 *  Created on: 09.04.2024
 *      Author: EliteBook HP840
 */

#include "LevelSensorApp.h"

LevelSensorApp::LevelSensorApp() {
    pinMode(D7, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D1, INPUT_PULLUP);
    pinMode(D2, INPUT_PULLUP);

}

void LevelSensorApp::loadSensors() {
    powerOn();
    delay(1000);
    level1 = digitalRead(D1);
    level2 = digitalRead(D2);
    powerOff();
}


void LevelSensorApp::insertSensorDataToHtml(WiFiClient &request) {
	strLevel1 = " Level1: " + String(level1, 3);
	strLevel2 = " Level2: " + String(level2, 3);
	//
	request.println("<p>" + strLevel1 + "</p>");
	request.println();
	request.println("<p>" + strLevel2 + "</p>");
	request.println();
}


void LevelSensorApp::sendResponse(WiFiClient &request) {
	Serial.println(header);
	if (header.indexOf("GET /set/?sleepTime=") >= 0) {
		    int pos = header.indexOf("=") + 1;
		    int endpos = header.indexOf(" ", pos);
		    String timeStr = header.substring(pos, endpos);
		    int time = timeStr.toInt();
		    if (time < 60) {
			time = 60;
		    }
		    if (time > 3600) {
			time = 3600;
		    }
		    setSleepTime(timeStr.toInt());
		    Serial.print("sleepTime = ");
		    Serial.println(sleepTime);
		    sendXML(request);
		    delay(10000);
		    doSliping();
	} else if (header.indexOf("GET /xml/") >= 0) {
		sendXML(request);
	} else if (header.indexOf("GET /") >= 0) {
		sendHTML(request);
	}
}


void LevelSensorApp::generateXML() {
	xmlStr.clear();
	xmlStr = xmlStr + "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n";
	xmlStr = xmlStr + "<devicestatus devicetype=\"99\" name=\"XKC-Y25\" devicedescription=\"Dezsö a szintmérö sensor\">\n";
	xmlStr = xmlStr + "    <valuesstatus>\n";
	xmlStr = xmlStr + "        <properties>\n";
	xmlStr = xmlStr + "            <property name=\"battery\" type=\"float\" value=\"" + vcc + "\" unit=\"V\" />\n";
	xmlStr = xmlStr + "            <property name=\"sleepTime\" type=\"int\" value=\"" + sleepTime + "\" unit=\"s\" />\n";
	xmlStr = xmlStr + "            <property name=\"level1\" type=\"int\" value=\"" + level1 + "\" unit=\"s\" />\n";
	xmlStr = xmlStr + "            <property name=\"level2\" type=\"int\" value=\"" + level2 + "\" unit=\"s\" />\n";
	xmlStr = xmlStr + "        </properties>\n";
	xmlStr = xmlStr + "    </valuesstatus>\n";
	xmlStr = xmlStr + "</devicestatus>\n";
	//
	Serial.println("Sent xml: ");
	Serial.println(xmlStr);
}

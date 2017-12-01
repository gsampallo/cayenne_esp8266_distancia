#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

#define TRIGGER 0
#define ECHO    2

// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";

unsigned long lastMillis = 0;

void setup() {
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);  
}

void loop() {
	Cayenne.loop();

	//Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
	if (millis() - lastMillis > 10000) {
		lastMillis = millis();


    long duration, distance;
    digitalWrite(TRIGGER, LOW);  
    delayMicroseconds(2); 
    
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10); 
    
    digitalWrite(TRIGGER, LOW);
    duration = pulseIn(ECHO, HIGH);
    distance = (duration/2) / 29.1;    
  
    Cayenne.virtualWrite(0, distance, TYPE_PROXIMITY, UNIT_CENTIMETER);
	}
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

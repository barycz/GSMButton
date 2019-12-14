// Author: Tomas Barak <baryhoemail@gmail.com>

#include <Arduino.h>
#include <Modem.h>

Modem modem(5, 4);

void setup() {
	Serial.begin(115200);
	Serial.println("Init");

	modem.Begin();
}

void loop()
{
	Serial.println("update");
	modem.Ping();
	delay(300);
}

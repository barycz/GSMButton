// Author: Tomas Barak <baryhoemail@gmail.com>

#pragma once

#include <Arduino.h>

namespace config
{
	static const String TargetNumber = "+XXXXXXXXXXXX";
	static const unsigned long CallCooldown = 2000; // millis
	static const unsigned long CallDuration = 20000; // millis
}

namespace pins
{
	static const uint8_t Button = 8;
	static const uint8_t LedExternal = 9;
	static const uint8_t LedInternal = LED_BUILTIN;
	static const uint8_t ModemRx = 5;
	static const uint8_t ModemTx = 4;

	namespace state
	{
		static const uint8_t ButtonPressed = LOW;
		static const uint8_t LedOn = LOW;
		static const uint8_t LedOff = HIGH;
		static const uint8_t LedInternalOn = HIGH;
		static const uint8_t LedInternalOff = LOW;
	}
}

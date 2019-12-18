// Author: Tomas Barak <baryhoemail@gmail.com>

#pragma once

#include <Arduino.h>

class DebugLed
{
public:
	enum class Mode
	{
		Off,
		Slow,
		Fast,
	};

	DebugLed(uint8_t pin);
	void Init();
	void Update();
	void SetMode(Mode state);

private:
	void SetValue(bool val, bool force = false);
	bool ShouldTransition() const;
	static unsigned long GetOffTime(Mode mode); // millis
	static unsigned long GetOnTime(Mode mode); // millis

	const uint8_t m_Pin;
	bool m_CurrentValue;
	Mode m_CurrentMode;
	unsigned long m_LastChange; // millis
};

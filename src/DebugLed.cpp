// Author: Tomas Barak <baryhoemail@gmail.com>

#include <DebugLed.h>
#include <config.h>

DebugLed::DebugLed(uint8_t pin)
	: m_Pin(pin)
	, m_CurrentValue(false)
	, m_CurrentMode(Mode::Off)
	, m_LastChange(0)
{

}

unsigned long DebugLed::GetOffTime(Mode mode)
{
	if (mode == Mode::Fast)
	{
		return 200;
	}
	else
	{
		return 1000;
	}
}

unsigned long DebugLed::GetOnTime(Mode mode)
{
	return 200;
}

void DebugLed::Init()
{
	pinMode(m_Pin, OUTPUT);
	SetValue(false, true);
}

void DebugLed::Update()
{
	if (m_CurrentMode == Mode::Off)
	{
		SetValue(false);
		return;
	}

	if (ShouldTransition())
	{
		SetValue(!m_CurrentValue);
	}
}

bool DebugLed::ShouldTransition() const
{
	const auto timeout = m_CurrentValue ? GetOnTime(m_CurrentMode) : GetOffTime(m_CurrentMode);
	return millis() - m_LastChange > timeout;
}

void DebugLed::SetValue(bool val, bool force)
{
	if (val == m_CurrentValue && force == false)
	{
		return;
	}

	m_CurrentValue = val;
	m_LastChange = millis();
	digitalWrite(m_Pin, val ? pins::state::LedOn : pins::state::LedOff);
}

void DebugLed::SetMode(Mode mode)
{
	if (m_CurrentMode == mode)
	{
		return;
	}

	m_CurrentMode = mode;
	if (mode != Mode::Off)
	{
		SetValue(true);
	}
}

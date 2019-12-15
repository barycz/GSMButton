// Author: Tomas Barak <baryhoemail@gmail.com>

#include <App.h>
#include <config.h>
#include <Arduino.h>

App::App()
	: m_LastCallRequest(0)
	, m_LastCall(0)
	, m_Modem(pins::ModemRx, pins::ModemTx)
{

}

void App::Setup()
{
	pinMode(pins::LedInternal, OUTPUT);
	pinMode(pins::LedExternal, OUTPUT);
	pinMode(pins::Button, INPUT_PULLUP);

	digitalWrite(pins::LedExternal, pins::state::LedExternalOff);
	digitalWrite(pins::LedInternal, pins::state::LedInternalOff);

	Serial.begin(115200);
	Serial.println("Init");

	m_Modem.Begin();
}

void App::Update()
{
	if (digitalRead(pins::Button) == pins::state::ButtonPressed)
	{
		m_LastCallRequest = millis();
	}

	if (m_LastCallRequest - m_LastCall > config::CallCooldown)
	{
		Call(config::TargetNumber, config::CallDuration);
		m_LastCall = m_LastCallRequest;
	}
}

bool App::Call(const String& number, unsigned long duration)
{
	if(m_Modem.Ping() == false)
	{
		return false;
	}

	if(m_Modem.Dial(number) == false)
	{
		return false;
	}

	delay(duration);
	return m_Modem.Hangup();
}

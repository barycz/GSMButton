// Author: Tomas Barak <baryhoemail@gmail.com>

#include <App.h>
#include <config.h>
#include <Arduino.h>

App::App()
	: m_LastCallRequest(0)
	, m_LastCall(0)
	, m_State(State::Idle)
	, m_Modem(pins::ModemRx, pins::ModemTx)
	, m_DebugLed(pins::LedExternal)
{

}

void App::Setup()
{
	m_DebugLed.Init();

	pinMode(pins::Button, INPUT_PULLUP);

	pinMode(pins::LedInternal, OUTPUT);
	digitalWrite(pins::LedInternal, pins::state::LedInternalOff);

	Serial.begin(115200);
	Serial.println("Init");

	m_Modem.Begin();
}

void App::UpdateIdle()
{
	if (m_LastCallRequest - m_LastCall > config::CallCooldown)
	{
		if(m_Modem.Dial(config::TargetNumber))
		{
			Serial.println("calling");
			m_State = State::InCall;
			m_DebugLed.SetMode(DebugLed::Mode::Fast);
		}
		else
		{
			Serial.println("call failed");
			m_DebugLed.SetMode(DebugLed::Mode::Slow);
			delay(100);
		}
	}
}

void App::UpdateInCall()
{
	if (millis() - m_LastCallRequest > config::CallDuration)
	{
		m_Modem.Hangup();
		m_State = State::Idle;
		m_DebugLed.SetMode(DebugLed::Mode::Off);
		m_LastCall = m_LastCallRequest;
	}
}

void App::Update()
{
	m_DebugLed.Update();
	if (digitalRead(pins::Button) == pins::state::ButtonPressed)
	{
		m_LastCallRequest = millis();
	}

	switch (m_State)
	{
	case State::Idle:
		UpdateIdle();
		break;

	case State::InCall:
		UpdateInCall();
		break;
	}
}

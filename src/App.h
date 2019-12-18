// Author: Tomas Barak <baryhoemail@gmail.com>

#pragma once

#include <Modem.h>
#include <DebugLed.h>

class App
{
public:
	App();

	void Setup();
	void Update();

private:
	enum class State
	{
		Idle,
		InCall,
	};

	void UpdateIdle();
	void UpdateInCall();

	unsigned long m_LastCallRequest;
	unsigned long m_LastCall;
	State m_State;
	Modem m_Modem;
	DebugLed m_DebugLed;
};

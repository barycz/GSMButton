// Author: Tomas Barak <baryhoemail@gmail.com>

#pragma once

#include <Modem.h>

class App
{
public:
	App();

	void Setup();
	void Update();

private:
	bool Call(const String& number, unsigned long duration);

	unsigned long m_LastCallRequest;
	unsigned long m_LastCall;
	Modem m_Modem;
};

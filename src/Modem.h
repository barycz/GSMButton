// Author: Tomas Barak <baryhoemail@gmail.com>

#pragma once

#include <SoftwareSerial.h>

// will use Serial to echo the communication
#define MODEM_DEBUG 1

class Modem
{
public:
	Modem(uint8_t receivePin, uint8_t transmitPin);

	void Begin(long baudRate = 9600);
	bool IsRegistered();
	bool Ping();
	bool Dial(const String& number);
	bool Hangup();

private:
	void Send(const String& line);
	void Send(const String& tk1, const String& tk2, const String& tk3);
	bool WaitFor(const String& resp, unsigned long timeoutMs = 1000);
	bool WaitFor(String& ioResp, const char wildcard = '*', unsigned long timeoutMs = 1000);

	void SendConfiguration();

	SoftwareSerial m_Comm;
};
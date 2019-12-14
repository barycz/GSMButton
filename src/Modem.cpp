// Author: Tomas Barak <baryhoemail@gmail.com>

#include <Modem.h>
#include <Arduino.h>

Modem::Modem(uint8_t receivePin, uint8_t transmitPin)
	: m_Comm(receivePin, transmitPin)
{

}

void Modem::Send(const String& line)
{
#if MODEM_DEBUG
	Serial.print("<- ");
	Serial.println(line);
#endif

	m_Comm.println(line);
}

bool Modem::WaitFor(const String& resp, unsigned long timeoutMs)
{
	const auto startTime = millis();
	unsigned pos = 0;
	do
	{
		if (pos == resp.length())
		{
#if MODEM_DEBUG
			Serial.print("-> ");
			Serial.println(resp);
#endif
			return true;
		}

		int ch = m_Comm.read();
		if(ch == -1)
		{
			continue;
		}

		if(ch == resp[pos])
		{
			++pos;
		}
		else
		{
			pos = 0;
		}

	} while(millis() - startTime < timeoutMs);

#if MODEM_DEBUG
	Serial.println("-> TIMEOUT");
#endif
	return false;
}

void Modem::DiscardResponse()
{
	while(m_Comm.available())
	{
		m_Comm.read();
	}
}

void Modem::Begin(long baudRate)
{
	m_Comm.begin(baudRate);
	SendConfiguration();
}

bool Modem::Ping()
{
	Send("AT");
	return WaitFor("OK");
}

void Modem::SendConfiguration()
{
	// initialize the baud rate detector
	Send("AT");
	WaitFor("OK");
	// disable echo
	Send("ATE0");
	WaitFor("OK");
}

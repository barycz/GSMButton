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

void Modem::Send(const String& tk1, const String& tk2, const String& tk3)
{
#if MODEM_DEBUG
	Serial.print("<- ");
	Serial.print(tk1);
	Serial.print(tk2);
	Serial.println(tk3);
#endif

	m_Comm.print(tk1);
	m_Comm.print(tk2);
	m_Comm.println(tk3);
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

bool Modem::WaitFor(String& ioResp, const char wildcard, unsigned long timeoutMs)
{
	const auto startTime = millis();
	unsigned pos = 0;
	do
	{
		if (pos == ioResp.length())
		{
#if MODEM_DEBUG
			Serial.print("-> ");
			Serial.println(ioResp);
#endif
			return true;
		}

		int ch = m_Comm.read();
		if(ch == -1)
		{
			continue;
		}

		if(ch == ioResp[pos] || ioResp[pos] == wildcard)
		{
			ioResp[pos] = ch;
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

void Modem::Begin(long baudRate)
{
	m_Comm.begin(baudRate);
	SendConfiguration();
}

bool Modem::IsRegistered()
{
	Send("AT+CREG?");
	String resp = "+CREG: *,*";
	if(WaitFor(resp) == false)
	{
		return false;
	}

	return resp.endsWith("1") || resp.endsWith("5");
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

bool Modem::Dial(const String& number)
{
	if (IsRegistered() == false)
	{
		return false;
	}

	Send("ATD+ ", number, ";");
	return WaitFor("OK");
}

bool Modem::Hangup()
{
	Send("ATH");
	return WaitFor("OK");
}

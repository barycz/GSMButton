// Author: Tomas Barak <baryhoemail@gmail.com>

#include <App.h>
#include <Arduino.h>

App g_App;

void setup()
{
	g_App.Setup();
}

void loop()
{
	g_App.Update();
}

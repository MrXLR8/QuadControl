
#include "ESP8266WiFi.h"




WiFiServer wifiServer(80);


void setup()
{


	pinMode(4, INPUT_PULLUP);
	Serial.begin(115200);
	delay(1000);

	if (digitalRead(4) == LOW)
	{
		WiFi.mode(WIFI_STA);
		Serial.println(connectTo("XLR8`s Wi-Fi", "wormoman8627fd039h0bg9"));
	}
	else
	{
		WiFi.mode(WIFI_AP);
		Serial.println(hostAP());
	}

	wifiServer.setNoDelay(true);
	wifiServer.begin();
}

IPAddress hostAP()
{
	char* ssid = "XLR8s_ESP82666";
	char* pass = "wormoman";

	Serial.println("AP Mode: ");
	Serial.println(ssid);
	Serial.println(pass);

	bool hidden = false;

	IPAddress local_IP(192, 168, 1, 1);
	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0);
	WiFi.softAPConfig(local_IP, gateway, subnet);
	WiFi.softAP(ssid, pass, 1, hidden, 1);



	return WiFi.softAPIP();
}



IPAddress connectTo(char* ssid, char* pass)
{
	Serial.println("Connection Mode: ");
	Serial.println(ssid);
	Serial.println(pass);
	WiFi.begin(ssid, pass);

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.println("Trying to connect...");
		delay(1000);
	}

	return WiFi.localIP();
}

void loop()
{
	WiFiClient client = wifiServer.available();
	if (client)
	{
		Serial.println("Client connected");
		while (client.connected())
		{
			if (Serial.available())
			{
				client.write(Serial.read());
			}
			while (client.available() > 0)
			{


				char c = client.read();

				Serial.write(c);

				client.write(c);
			}
			delay(10);
		}

		if (Serial.available())
		{
			client.write(Serial.read());
		}

		client.stop();
		Serial.println("Client disconnected");
	}

}




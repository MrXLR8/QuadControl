

#include "ESP8266WiFi.h"

#include "Order.h"
#include <vector>

//WF -подключение
//WI -информация об ИП
//WC - соединения

const uint port = 49123;
WiFiServer wifiServer(port);
using namespace std;

void setup()
{


	pinMode(4, INPUT_PULLUP);
	Serial.begin(76800);
	delay(1000);

	if (digitalRead(4) == LOW)
	{
		WiFi.mode(WIFI_STA);
		connectTo("XLR8`s Wi-Fi", "wormoman8627fd039h0bg9");
	}
	else
	{
		WiFi.mode(WIFI_AP);
		hostAP();
	}

	wifiServer.setNoDelay(true);
	wifiServer.begin();
}

IPAddress hostAP()
{
	char* ssid = "XLR8s_ESP82666";
	char* pass = "wormoman";



	vector<String> arg;
	arg.push_back("AP");
	arg.push_back(ssid);
	arg.push_back(pass);

	Order connection("WF", arg);


	Serial.println(connection.ToString());


	bool hidden = false;

	IPAddress local_IP(192, 168, 1, 123);
	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0);
	WiFi.softAPConfig(local_IP, gateway, subnet);
	WiFi.softAP(ssid, pass, 1, hidden, 1);

	vector<String> arg1;
	arg1.push_back(WiFi.softAPIP().toString());

	Order connection1("WI", arg1);
	Serial.println(connection1.ToString());

	return WiFi.softAPIP();
}



IPAddress connectTo(char* ssid, char* pass)
{

	vector<String> arg;
	arg.push_back("STA");
	arg.push_back(ssid);
	arg.push_back(pass);
	
	Order connection("WF", arg);

	
	Serial.println(connection.ToString());
	
	
	WiFi.begin(ssid, pass);

	while (WiFi.status() != WL_CONNECTED)
	{

		delay(1000);
	}

	vector<String> arg1;
	arg1.push_back(WiFi.localIP().toString());
	Order connection1("WI", arg1);
	Serial.println(connection1.ToString());
	return WiFi.localIP();
}	

void loop()
{
	WiFiClient client = wifiServer.available();
	if (client)
	{
		vector<String> arg;
		arg.push_back("+");
		Order clientconnect("WC", arg);
		Serial.println(clientconnect.ToString());

		while (client.connected())
		{
			if (Serial.available())
			{
				client.write(Serial.read()); // то что пришло по серийнику отправить по вайфаю
			}
			while (client.available() > 0)
			{


				char c = client.read();

				Serial.write(c);  // то что пришло по вайфаю отправить по серийнику

				//client.write(c); отправить обратно
			}
			delay(10);
		}

		//if (Serial.available())
		//{
		//	client.write(Serial.read());
		//}


		client.stop();

		// сказать по юзб что клиент отключилься
		vector<String> arg1;
		arg1.push_back("-");
		Order clientdisc("WC", arg1);
		Serial.println(clientdisc.ToString());
	}

}




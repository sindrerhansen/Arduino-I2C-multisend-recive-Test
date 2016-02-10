//Mega

#include <Wire.h>

#define MEGA_ADDRESS 0x9
#define NANO_ADDRESS 0x8
#define UNO_ADDRESS 0x7

const int conterOffset = 0;
int conter = 0 + conterOffset;
const String MyName = "Mega";

void setup() {
	Serial.begin(9600);
	Wire.begin(MEGA_ADDRESS);
	Wire.onReceive(receiveEvent);
}

void loop() {
	if (conter<(conterOffset + 100))
	{
		conter = conter + 1;
	}
	else
	{
		conter = conterOffset;
	}
	char charSendBuffer[20];
	String sendString = MyName + " sending:" + String(conter);
	sendString.toCharArray(charSendBuffer, 20);
	Wire.beginTransmission(NANO_ADDRESS);
	Wire.write(charSendBuffer);
	Wire.endTransmission();
	Wire.beginTransmission(UNO_ADDRESS);
	Wire.write(charSendBuffer);
	Wire.endTransmission();
	Serial.println("Sending " + String(conter));
	delay(1000);
}

void receiveEvent(int howMany) {
	char charReadBuffer[20] = "";
	int charIndicator = 0;
	while (Wire.available() > 0) {
		char c = Wire.read();
		charReadBuffer[charIndicator] = c;
		charIndicator++;
	}
	String str(charReadBuffer);
	Serial.println(str);

}
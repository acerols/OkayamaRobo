#include <Arduino.h>
#include "AWDControl.hpp"

void setup() {
  	// put your setup code here, to run once:
	pinMode(2, OUTPUT);	
	pinMode(3, OUTPUT);
  	pinMode(4, OUTPUT);
  	pinMode(5, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	const int MP = 200;
	AwdControl ctr(2,3,4,5,6,7,8,9);
	ctr.movefored();
	/*
	digitalWrite(2, LOW);
	analogWrite(3, MP);
	digitalWrite(4, LOW);
	analogWrite(5, MP);
	delay(1000);
	for(int i = 2; i <= 5; i++){
		digitalWrite(i, LOW);
	}
	
	delay(1000);
	digitalWrite(3, LOW);
	analogWrite(2, MP);
	digitalWrite(5, LOW);
	analogWrite(4, MP);
	*/
	while(1);
}
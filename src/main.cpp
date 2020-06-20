#include <Arduino.h>
#include "AWDControl.hpp"

const static int D1M1D = 2;
const static int D1M1P = 3;
const static int D1M2D = 4;
const static int D1M2P = 5;
const static int D2M1D = 6;
const static int D2M1P = 7;
const static int D2M2D = 8;
const static int D2M2P = 9;

void setup() {
  	// put your setup code here, to run once:
	pinMode(D1M1D, OUTPUT);	
	pinMode(D1M1P, OUTPUT);
  	pinMode(D1M2D, OUTPUT);	
	pinMode(D2M2P, OUTPUT);
	pinMode(D2M1P, OUTPUT);
  	pinMode(D2M2D, OUTPUT);	
	pinMode(D2M2P, OUTPUT);
	
	Serial.begin(9600);
}

void loop() {
	// put your main code here, to run repeatedly:
	const int MP = 100;
	AwdControl ctr(D1M1D, D1M1P, D1M2D, D1M2P,
					D2M1D, D2M1P, D2M2D, D2M2P
	);
	ctr.movefored();
	//analogWrite(D1M1P, 174);
	//analogWrite(D2M2P, 174);
	while(1);
}
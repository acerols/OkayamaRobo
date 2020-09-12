#include <Arduino.h>

#include "AWDControl.hpp"
#include <Connection.hpp>
#include <debug.hpp>

const static int D1M1D = 2;
const static int D1M1P = 3;
const static int D1M2D = 4;
const static int D1M2P = 5;
const static int D2M1D = 7;
const static int D2M1P = 6;
const static int D2M2D = 8;
const static int D2M2P = 9;
const static int USSensorLeft = 0;
const static int USSensorRight = 1;


int dt[20] = {0};

Nano nano(10, 11);

void setup() {
  // put your setup code here, to run once:
  pinMode(D1M1D, OUTPUT);	
  pinMode(D1M1P, OUTPUT);
  pinMode(D1M2D, OUTPUT);	
  pinMode(D1M2P, OUTPUT);
  pinMode(D2M1D, OUTPUT);
  pinMode(D2M1P, OUTPUT);
  pinMode(D2M2D, OUTPUT);	
  pinMode(D2M2P, OUTPUT);
  nano.begin(115200);
  Serial.begin(115200);
  Serial.println("Helloworld");
}

void test()
{
	LineSensor LS;
	while(1){
		int recnum = nano.available();
		int rec = nano.RecData(LS);
		//Serial.print("RecNumP : ");
		//Serial.println(recnum);
		if(rec > 0){
			Serial.print("Rec : ");
			Serial.println(LS.LSFront, DEC);
		}

	}
}

void loop() {
	LineSensor LS;
	SendData SD;
	const int MotorCool = 1000; //Motor Cool Time
	AwdControl ctr(D1M1D, D1M1P, D1M2D, D1M2P,
		  D2M1D, D2M1P, D2M2D, D2M2P
	);
	nano.RecData(LS);
	ctr.movefored();

	if(InputRobo(dt, CONTROL) > 0){
		SD.USSL = analogRead(0);
		SD.USSR = analogRead(1);
		SD.BSFront = analogRead(2);
		SD.BSLeft = analogRead(3);
		SD.BSRight = analogRead(4);
		SD.BSRear = analogRead(5);
		SendRobo(SD, 0x01);
	}
	else{
		//assert("Connection Failed!!");
	}
	delay(10);
  
}

void ControlRobo(AwdControl &robo, int *cmd)
{
	int LX = cmd[3];
	int LY = cmd[4];
	int RX = cmd[5];

	if(LY > (127 + 60)){
		robo.movedir(90, 250);
	}
	else if(LY < (127 - 60)){
		robo.movedir(270, 250);
	}
	else if(LX > (127 + 60)){
		robo.movedir(180, 250);
	}
	else if(LX < (127 - 60)){
		robo.movedir(0, 250);
	}
	else if(RX > (126 + 60)){
		robo.moveturn(1, 180);
	}
	else if(RX < (127 - 60)){
		robo.moveturn(-1, 180);
	}
	else{
		robo.movedir(0, 0);
	}
  
}

int getUSLegt()
{
  int len = analogRead(USSensorLeft);
  return (len * 3);
}

int getUSRight()
{
  int len = analogRead(USSensorRight);
  return (len * 3);
}

void SendRobo()
{

}
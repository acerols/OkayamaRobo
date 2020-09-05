#include <Arduino.h>
#include <SoftwareSerial.h>
#include "AWDControl.hpp"
#include <Connection.hpp>

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

SoftwareSerial ms(10, 11);

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
  ms.begin(115200);
  Serial.begin(115200);
  Serial.println("Helloworld");
}

void loop() {
  // put your main code here, to run repeatedly:
  
	const int MotorCool = 1000; //Motor Cool Time
	AwdControl ctr(D1M1D, D1M1P, D1M2D, D1M2P,
		  D2M1D, D2M1P, D2M2D, D2M2P
	);
	ctr.movefored();

	if(InputRobo(dt) > 0){
		int LX = (dt[3] - 128) * -1;
		int LY = dt[4] - 128;
		//int RX = dt[5] - 128;
		Serial.println(LX, DEC);
		ms.print("LX : ");
		ms.print(LX, DEC);
		ms.print(" LY : ");
		ms.println(LY, DEC);
		ctr.movedir(LX, LY, 250);
		/*
		if(LY > (127 + 60)){
			ctr.movedir(90, 250);
		}
		else if(LY < (127 - 60)){
			ctr.movedir(270, 250);
		}
		else if(LX > (127 + 60)){
			ctr.movedir(180, 250);
		}
		else if(LX < (127 - 60)){
			ctr.movedir(0, 250);
		}
		else if(RX > (127 + 60)){
			ctr.moveturn(1, 180);
		}
		else if(RX < (127 - 60)){
			ctr.moveturn(-1, 180);
		}
		else{
			ctr.movedir(0, 0);
		}
		*/
	}
	else{
		ms.println("NO");
	}
	delay(20);
  /*
  ctr.movedir(0, 250);
  delay(1000);
  ctr.movedir(0, 0);
  delay(MotorCool);
  ctr.movedir(90, 250);
  delay(1000);
  while(1);
  ctr.movedir(0, 0);
  delay(MotorCool);
  ctr.movedir(180, 250);
  delay(1000);
  ctr.movedir(0, 0);
  delay(MotorCool);
  ctr.movedir(270, 250);
  delay(1000);
  ctr.movedir(0, 0);
  delay(MotorCool);
  ctr.movedir(0, 0);
  delay(1000);
  */
  
}

void ControlRobo(AwdControl &robo, int *cmd)
{
	int LX = cmd[3];
	int LY = cmd[4];
	int RX = cmd[5];

	ms.print("LX : ");
	ms.print(LX, DEC);
	ms.print(" LY : ");
	ms.println(LY, DEC);
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
#include <Arduino.h>
#include <string.h>

#define debug
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


int dt[20] = {0};

Nano nano(10, 11);

int16_t GoalAngle = 0;

void ControlRobo(AwdControl *robo, AgentOrder *ao);

//SoftwareSerial debugs(10, 11);
void setup()
{
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
	//debugs.begin(115200);
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
	AgentOrder AO;
	static int loopcast = 0;
	AwdControl ctr(D1M1D, D1M1P, D1M2D, D1M2P,
		  D2M1D, D2M1P, D2M2D, D2M2P
	);

	nano.RecData(LS);
	AO.velocity = 0;
	AO.omega = 0;
	if(InputRobo(&AO) > 0){
		GoalAngle = AO.TargetAngle;
		//setSD(SD);
		SendRobo(SD, 0x01);
		loopcast = 0;
		ControlRobo(&ctr, &AO);
	}
	else{
		loopcast++;
		AO.velocity = 0;
		AO.omega = 0;
		AO.NowAngle = 0;
		AO.TargetAngle = GoalAngle;
		if(loopcast > 10){
			AO.velocity = 0;
			AO.omega = 0;
			ControlRobo(&ctr, &AO);
		}
		//assert("Connection Failed!!");
	}
	delay(20);
  
}

void ControlRobo(AwdControl *robo, AgentOrder *ao)
{
	if(ao->velocity != 0){
		robo->movedir((uint8_t)ao->omega, ((uint8_t)ao->velocity));
		robo->turn_pid((int16_t)ao->NowAngle, (int16_t)ao->TargetAngle, false);
	}
	else{
		nano.println("PID");
		robo->turn_pid((int16_t)ao->NowAngle, (int16_t)ao->TargetAngle, true);
	}
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


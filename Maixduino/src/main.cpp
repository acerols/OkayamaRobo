#include <Arduino.h>


#ifdef  DEBUG
#undef  DEBUG
#endif

#include "AWDControl.hpp"

const static int D1M1D = 2;
const static int D1M1P = 3;
const static int D1M2D = 4;
const static int D1M2P = 5;
const static int D2M1D = 6;
const static int D2M1P = 7;
const static int D2M2D = 8;
const static int D2M2P = 9;

int InputRobo(int *data);

void setup() {
  	// put your setup code here, to run once:
	pinMode(D1M1D, OUTPUT);	
	pinMode(D1M1P, OUTPUT);
	pinMode(D1M2D, OUTPUT);	
	pinMode(D2M2P, OUTPUT);
	pinMode(D2M1P, OUTPUT);
  pinMode(D2M2D, OUTPUT);	
	pinMode(D2M2P, OUTPUT);
	
	Serial.begin(115200, 10, 11);
  Serial.println("Helloworld");
}

void loop() {
	// put your main code here, to run repeatedly:
	
  int dt[20];
  const int MotorCool = 1000; //Motor Cool Time
  AwdControl ctr(D1M1D, D1M1P, D1M2D, D1M2P,
					D2M1D, D2M1P, D2M2D, D2M2P
	);
  /*
  ctr.movedir(0, 250);
  delay(1000);
  ctr.movedir(0, 0);
  delay(MotorCool);
  ctr.movedir(90, 250);
  delay(1000);
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
	if(InputRobo(dt) > 0){
		Serial.println("OK");
	}
	else{
		Serial.println("No");
	}
	delay(50);
  
  //
	//analogWrite(D1M1P, 174);
	//analogWrite(D2M2P, 174);
}
/*
#include <SoftwareSerial.h>

SoftwareSerial ms(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  ms.begin(115200);
  ms.println("HelloWorld");
  
}

static long long i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("HelloWorld");
  if(i == 0 ){
    digitalWrite(8, HIGH);
    delay(1000);
    i++;
  }
  int data[20];
  if(InputRobo(data) == 1){
    Serial.println("OK");
    for(int j = 0; j < 10; j++){
      ms.println(data[j]);
    }
    digitalWrite(8, HIGH);
  }
  else{
    Serial.println("No");
    digitalWrite(8, LOW);
  }
  delay(20);
}
*/

int InputRobo(int *data)
{
  if(Serial.available() > 12){
    int magic = Serial.read();
    if(magic == 0xff){
      int fuct;
      fuct = Serial.read();
      if(fuct == 0x10){
        int sizes = Serial.read();
        int8_t checksum = 0;
        for(int i = 0; i < sizes; i++){
          data[i] = Serial.read();
          checksum = checksum ^ data[i];
        }
        int dt = Serial.read();
        if(checksum == dt){
          return 1;
        }
      }
      else if(fuct == 0x01){
        
      }
    }
    else{
      return -1;
    }
  }
  return -1;
}

#include <Arduino.h>

const static int LSFront = 0;
const static int LSLeft = 1;
const static int LSRight = 2;
const static int LSRear = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  Send();
}

void Send()
{
  byte data[10];
  int LSFdata = analogRead(LSFront);
  int LSLdata = analogRead(LSLeft);
  int LSRdata = analogRead(LSRight);
  int LSRedata = analogRead(LSRear);
  
  data[0] = 0x64;
  data[1] = LSFdata & 0xff;
  data[2] = (LSFdata >> 8) & 0xff;
  data[3] = LSLdata & 0xff;
  data[4] = (LSLdata >> 8) & 0xff;
  data[5] = LSRdata & 0xff;
  data[6] = (LSRdata >> 8) & 0xff;
  data[7] = LSRedata & 0xff;
  data[8] = (LSRedata >> 8) & 0xff;
  byte checksum = 0;
  for(int i = 1; i <= 8; i++){
    checksum ^= data[i];
  }
  data[9] = checksum;
  for(int i = 0; i < 10; i++){
    Serial.write(data[i]);
    
  }
  delay(20);
}
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include <Controller.hpp>

const int CONTROL = 0x10;
const int AGENT = 0x20;

uint8_t retcs();

struct Rec1Data
{
};

struct Rec2Data
{
};

struct SendData
{
    uint16_t USSL;    //Ultra Sonic Sensor Light little 1byte
    uint16_t USSR;    //USSL Little 2byte
    uint16_t BSFront;
    uint16_t BSLeft;
    uint16_t BSRight;
    uint16_t BSRear;
};

struct LineSensor
{
    int LSFront;
    int LSLeft;
    int LSRight;
    int LSRear;
};

int InputRobo(int *data);
int InputRobo(AgentOrder *ao);
byte Read2byte(int16_t *data);
//int RecData(LineSensor *LS, SoftwareSerial *Nano);
void SendRobo(SendData &sd, int func);
void setSD(SendData &sd);

//Arduino Nanoとの通信方式を包括したSoftwareSerialの継承
class Nano : public SoftwareSerial{
public:
    Nano(int rx, int tx);
    int RecData(LineSensor &LS);
    byte Rec2byte(int &data);
};

#endif

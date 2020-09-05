#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <Arduino.h>

struct Rec1Data
{
};

struct Rec2Data
{
};

struct SendData
{
    uint8_t USSL_L1;    //Ultra Sonic Sensor Light little 1byte
    uint8_t USSL_L2;    //USSL Little 2byte
    uint8_t USSR_L1;
    uint8_t USSR_L2;
    uint8_t BSFront;
    uint8_t BSLeft;
    uint8_t BSRight;
    uint8_t BSRear;
};

struct LineSensor
{
};

int InputRobo(int *data);

#endif

#include <Arduino.h>

const static int USSensorLeft = A4;
const static int USSensorRight = A5;
const static int BSensorFront = A0;
const static int BSensorLeft = A1;
const static int BSensorRight = A2;
const static int BSensorRear = A3;

int getUSSLeft();
int getUSSRight();
int getBSFront();
int getBSLeft();
int getBSRight();
int getBSRear();
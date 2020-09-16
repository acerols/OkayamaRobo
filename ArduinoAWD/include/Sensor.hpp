#include <Arduino.h>

const static int USSensorLeft = 0;
const static int USSensorRight = 1;
const static int BSensorFront = 2;
const static int BSensorLeft = 3;
const static int BSensorRight = 4;
const static int BSensorRear = 5;

int getUSSLeft();
int getUSSRight();
int getBSFront();
int getBSLeft();
int getBSRight();
int getBSRear();
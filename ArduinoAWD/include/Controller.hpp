#include <Arduino.h>

struct Controller {
    uint8_t Button1;
    uint8_t Button2;
    uint8_t CrossButton;
    uint8_t JoyStickLeft[2];
    uint8_t JoyStickRight[2];
    uint8_t Key;
};

struct AgentOrder{
    int16_t velocity;   //Move Velocity
    int16_t omega;  //Move Direction
    int16_t NowAngle;
    int16_t TargetAngle;
};
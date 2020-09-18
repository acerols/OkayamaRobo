#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <Arduino.h>
#include <string.h>

void assert(String msg)
{
#ifdef debug
    Serial.println(msg);
#endif
}

void assert(String msg, int value, int decode)
{
#ifdef debug
    Serial.print(msg);
    Serial.println(value, decode);
#endif
}

void assert(const char *msg, int value, int decode, SoftwareSerial *debugs)
{
#ifdef debug
    debugs->print(msg);
    debugs->println(value, decode);
#endif
}

#endif

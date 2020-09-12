#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <Arduino.h>
#include <string.h>

#define debug

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

#endif

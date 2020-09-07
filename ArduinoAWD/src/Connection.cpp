#include <Connection.hpp>
#include <SoftwareSerial.h>

int InputRobo(int *data)
{
    if (Serial.available() > 12)
    {
        int magic = Serial.read();
        if (magic == 0xff)
        {
            int fuct;
            fuct = Serial.read();
            if (fuct == 0x10)
            {
                int sizes = Serial.read();
                uint8_t checksum = 0;
                for (int i = 0; i < sizes && i < 18; i++)
                {
                    data[i] = Serial.read();
                    checksum = checksum ^ data[i];
                }
                uint8_t dt = Serial.read();
                if (checksum == dt)
                {
                    return 1;
                }
            }
            else if (fuct == 0x01)
            {
            }
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

int RecData(LineSensor *LS, SoftwareSerial *Nano)
{
    byte checksum = 0;
    int recnum = Nano->available();
    int data[10];

    LS->LSFront = 0;
    LS->LSLeft = 0;
    LS->LSRight = 0;
    LS->LSRear = 0;
    if(Nano->available() > 0){
        byte magic = Nano->read();
        if(magic == 0x64){
            int data1, data2;
            data1 = Nano->read();
            data2 = Nano->read();
            checksum ^= data1;
            checksum ^= data2;
            data[0] = ((data2 << 8) & 0xff00) | (data1 & 0xff);
            //data[0] = Nano->read();
            //data[0] = (Nano->read() << 8) | data[0];
            data1 = Nano->read();
            data2 = Nano->read();
            checksum ^= data1;
            checksum ^= data2;
            data[1] = ((data2 << 8) & 0xff00) | (data1 & 0xff);
            data1 = Nano->read();
            data2 = Nano->read();
            checksum ^= data1;
            checksum ^= data2;
            data[2] = ((data2 << 8) & 0xff00) | (data1 & 0xff);
            data1 = Nano->read();
            data2 = Nano->read();
            checksum ^= data1;
            checksum ^= data2;
            data[3] = ((data2 << 8) & 0xff00) | (data1 & 0xff);
            byte checknum = Nano->read();
            /*
            Serial.print("NanoSum : ");
            Serial.println(checknum, DEC);
            Serial.print("UnoSum :");
            Serial.println(checksum , DEC);
            */
            if(checknum == checksum){  
                LS->LSFront = data[0];
                LS->LSLeft = data[1];
                LS->LSRight = data[2];
                LS->LSRear = data[3];
                return 10;
            }
        }
    }
  return -1;
}

byte Rec2byte(SoftwareSerial *ss, int *data)
{
    byte data1, data2;
    byte checksum = 0;
    data1 = ss->read();
    data2 = ss->read();
}
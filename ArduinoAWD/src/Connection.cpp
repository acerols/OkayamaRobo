#include <Connection.hpp>
#include <SoftwareSerial.h>
#include <Sensor.hpp>

int InputRobo(int *data, int func)
{
    if (Serial.available() > 12)
    {
        int magic = Serial.read();
        if (magic == 0xff)
        {
            int funcPC;
            funcPC = Serial.read();
            //Recieved PC Controller Data
            if (funcPC == CONTROL && func == CONTROL)
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
            //Received Agent Order and compass sensor data using IMU
            else if (funcPC == AGENT && func == AGENT){
                int velocity;   //-255 ~ 255
                velocity = Serial.read();
                int8_t omega;   //-180 ~ 180
                omega = Serial.read();
                byte nowThetaL, nowThetaH;
                nowThetaL = Serial.read();
                nowThetaH = Serial.read();
                int nowTheta = (nowThetaH << 8) & 0xff00 | (nowThetaL & 0xff);  
                byte targetThetaL, targetThetaH;
                targetThetaL = Serial.read();
                targetThetaH = Serial.read();
                int targetTheta = (short)(((targetThetaH << 8) & 0xff00) | (targetThetaL & 0xff));
            }
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

void SendRobo(SendData &sd, int func)
{
    byte buffer[20];
    byte checksum = 0;
    buffer[0] = 0x64;   //magic number
    if(func == 0x01){
        buffer[1] = 0x01;   //protocol function
        buffer[2] = (sd.USSL & 0xff);
        buffer[3] = ((sd.USSL >> 8) & 0xff);
        buffer[4] = (sd.USSR & 0xff);
        buffer[5] = ((sd.USSR >> 8) & 0xff);
        buffer[6] = (sd.BSFront & 0xff);
        buffer[7] = (sd.BSFront >> 8) & 0xff;
        buffer[8] = (sd.BSLeft & 0xff);
        buffer[9] = (sd.BSLeft >> 8) & 0xff;
        buffer[10] = (sd.BSRight & 0xff);
        buffer[11] = (sd.BSRight >> 8) & 0xff;
        buffer[12] = (sd.BSRear & 0xff);
        buffer[13] = (sd.BSRear >> 8) & 0xff;
        for(int i = 2; i <= 13; i++){
            checksum ^= buffer[i];
        }
        buffer[14] = checksum;
        for(int i = 0; i <= 14; i++){
            Serial.write(buffer[i]);
        }
    }

}

//get Sensor data to SendData
void setSD(SendData &sd)
{
    sd.USSL = (uint16_t)getUSSLeft();
    sd.USSR = (uint16_t)getUSSRight();
    sd.BSFront = (uint16_t)getBSFront();
    sd.BSLeft = (uint16_t)getBSLeft();
    sd.BSRight = (uint16_t)getBSRight();
    sd.BSRear = (uint16_t)getBSRight();
}

//コンストラクタ　コピー
Nano::Nano(int rx, int tx) : SoftwareSerial(rx, tx)
{
}

//Nanoとの独自通信方式を追加
int Nano::RecData(LineSensor &LS)
{
    byte checksum = 0;
    int recnum = available();
    int data[10] = {0};

    LS.LSFront = 0;
    LS.LSLeft = 0;
    LS.LSRight = 0;
    LS.LSRear = 0;
    if(recnum > 0){
        byte magic = read();
        if(magic == 0x64){
            //int size = read();
            checksum ^= Rec2byte(data[0]);
            //data[0] = Nano->read();
            //data[0] = (Nano->read() << 8) | data[0];
            checksum ^= Rec2byte(data[1]);
            checksum ^= Rec2byte(data[2]);
            checksum ^= Rec2byte(data[3]);
            byte checknum = read();
            /*
            Serial.print("NanoSum : ");
            Serial.println(checknum, DEC);
            Serial.print("UnoSum :");
            Serial.println(checksum , DEC);
            */
            if(checknum == checksum){  
                LS.LSFront = data[0];
                LS.LSLeft = data[1];
                LS.LSRight = data[2];
                LS.LSRear = data[3];
                return 10;
            }
        }
    }
  return -1;
}

//Recieve 2 byte 
//return checksum( xor )
byte Nano::Rec2byte(int &data)
{
    byte data1, data2;
    byte checksum = 0;
    data1 = read();
    data2 = read();
    data = (int)((short)((data2 << 8) | (data1 & 0xff)));
    checksum = checksum ^ data1 ^ data2;
    return checksum;
}
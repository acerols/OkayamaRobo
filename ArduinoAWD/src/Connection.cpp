#include <Connection.hpp>

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
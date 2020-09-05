#ifndef __AWDCONTROL_HPP__
#define __AWDCONTROL_HPP__

#include <Arduino.h>
#include <math.h>

namespace OkayamaRobo
{

const int MOTORNUM = 4;



class AwdControl
{
private:
  int D1M1D;
  int D1M1P;
  int D1M2D;
  int D1M2P;
  int D2M1D;
  int D2M1P;
  int D2M2D;
  int D2M2P;
  void ControlD1M1(int dir, int sp);
  void ControlD1M2(int dir, int sp);
  void ControlD2M1(int dir, int sp);
  void ControlD2M2(int dir, int sp);
public:
  AwdControl(int d1m1d, int d1m1p, int d1m2d, int d1m2p, int d2m1d, int d2m1p, int d2m2d, int d2m2p);
  void setD1(int m1d, int m1p, int m2d, int m2p);
  void setD2(int m1d, int m1p, int m2d, int m2p);
  void movefored(void);
  void movedir(int deg, int speeds);
};

void AwdControl::ControlD1M1(int dir, int sp)
{
	if(dir == 1){
		analogWrite(D1M1D, 0);
	  	analogWrite(D1M1P, sp);
	}
	else{
	  	analogWrite(D1M1D, sp);
		analogWrite(D1M1P, 0);
	}  
}

void AwdControl::ControlD1M2(int dir, int sp)
{
	if(dir == 1){
		analogWrite(D1M2D, 0);
		analogWrite(D1M2P, sp);
	}
	else{
		analogWrite(D1M2D, sp);
		analogWrite(D1M2P, 0);
	
	}
}

void AwdControl::ControlD2M1(int dir, int sp)
{
	if(dir == 1){
		analogWrite(D2M1D, 0);
		analogWrite(D2M1P, sp);
	}
	else{
		analogWrite(D2M1D, sp);
		analogWrite(D2M1P, 0);
	
	}
}

void AwdControl::ControlD2M2(int dir, int sp)
{
	if(dir == 1){
		analogWrite(D2M2D, 0);
		analogWrite(D2M2P, sp);
	}
	else{
		analogWrite(D2M2D, sp);
		analogWrite(D2M2P, 0);
	
	}
}

AwdControl::AwdControl(int d1m1d, int d1m1p, int d1m2d, int d1m2p, int d2m1d, int d2m1p, int d2m2d, int d2m2p)
{
  this->setD1(d1m1d, d1m1p, d1m2d, d1m2p);
  this->setD2(d2m1d, d2m1p, d2m2d, d2m2p);
}

void AwdControl::setD1(int m1d, int m1p, int m2d, int m2p)
{
  D1M1D = m1d;
  D1M1P = m1p;
  D1M2D = m2d;
  D1M2P = m2p;
  analogWrite(D1M1D, 0);
  analogWrite(D1M1P, 0);
  analogWrite(D1M2D, 0);
  analogWrite(D1M2P, 0);
  /*
  Serial.print(D1M1D);
  Serial.print(" ");
  Serial.print(D1M1P);
  Serial.print(" ");
  Serial.print(D1M2D);
  Serial.print(" ");
  Serial.print(D1M2P);
  Serial.println(" ");
  */
}

void AwdControl::setD2(int m1d, int m1p, int m2d, int m2p)
{
  D2M1D = m1d;
  D2M1P = m1p;
  D2M2D = m2d;
  D2M2P = m2p;
  analogWrite(D2M1D, 0);
  analogWrite(D2M1P, 0);
  analogWrite(D2M2D, 0);
  analogWrite(D2M2P, 0);
  /*
  Serial.print(D2M1D);
  Serial.print(" ");
  Serial.print(D2M1P);
  Serial.print(" ");
  Serial.print(D2M2D);
  Serial.print(" ");
  Serial.print(D2M2P);
  Serial.println(" ");
  */
}

const double pi = 3.141592;
static const int MV[4][2] ={
    {1, -1},
    {1, 1},
    {-1, -1},
    {-1, 1},
};

static const int sp = 175;

double deg2rad(int deg)
{
    return (deg * (pi / 180));
}

int deg2out(int deg, int MN)
{
    double rad = deg * (pi / 180);
    double Y = sin(rad);
    double X = cos(rad);
    int OUT = (
        Y * MV[MN-1][0] * sp +
        X * MV[MN-1][1] * sp
    );
    return OUT;
}

int deg2out(int deg, int MN, int speeds)
{
    int spd;
    
    //else if(speeds < 0) speeds = 0;
    /* 
    角度に対するＰＷＭ最大出力を決める
    */
    double c = cos(deg2rad(deg));
    double s = sin(deg2rad(deg));
    double t = max(abs(c), abs(s));
    spd = 250 / (1.0 / t);
    //スピードが
    if (speeds > 250){
        speeds = spd;
    }

    double rad = deg * (pi / 180);
    double Y = sin(rad);
    double X = cos(rad);
    int y = (int)(Y * (double)speeds);
    int x = (int)(X * (double)speeds);
#ifdef DEBUG
    Serial.print("X ");
    Serial.print(x);
    Serial.print(" MX ");
    Serial.print(x * MV[MN-1][0]);
    Serial.print(" Y ");
    Serial.print(y);
    Serial.print(" MY ");
    Serial.print(y * MV[MN-1][1]);
#endif
    int OUT = (
        y * MV[MN-1][0] +
        x * MV[MN-1][1]
    );
#ifdef DEBUG
    Serial.print(" spd ");
    Serial.print(speeds);  
    Serial.print(" OUT ");
    Serial.print(OUT);
    Serial.println(" ");
    Serial.print("max spd");
    Serial.println(spd);
#endif
    return OUT;
}

void AwdControl::movefored(void)
{
    int v[4][2] = {0};

    for(int i = 1; i < MOTORNUM+1; i++){
        v[i-1][1] = deg2out(90, i, 250);
        if(v[i-1][1] > 0){
            v[i-1][0] = 1;
        }
        else{
            v[i-1][0] = -1;
        }
#ifdef  DEBUG
        Serial.print(i);
        Serial.print(" : output : ");
        Serial.println(v[i-1][1]);
#endif
    }
    ControlD1M1(v[0][0], v[0][1]);
    ControlD1M2(v[1][0], v[1][1]);
    ControlD2M1(v[2][0], v[2][1]);
    ControlD2M2(v[3][0], v[3][1]);
}

void AwdControl::movedir(int deg, int speeds)
{
    int v[4][2] = {0};

    if(speeds == 0){
        ControlD1M1(0, 0);
        ControlD1M2(0, 0);
        ControlD2M1(0, 0);
        ControlD2M2(0, 0);
        return;
    }

    for(int i = 1; i < MOTORNUM+1; i++){
        v[i-1][1] = deg2out(deg, i, speeds);
        if(v[i-1][1] > 0){
            v[i-1][0] = 1;
        }
        else{
            v[i-1][0] = -1;
        }
    }
#ifdef  DEBUG

    Serial.print(v[0][1]);
    Serial.print(" ");
    Serial.print(v[1][1]);
    Serial.print(" ");
    Serial.print(v[2][1]);
    Serial.print(" ");
    Serial.print(v[3][1]);
    Serial.println();
    Serial.print(v[0][0]);
    Serial.print(" ");
    Serial.print(v[1][0]);
    Serial.print(" ");
    Serial.print(v[2][0]);
    Serial.print(" ");
    Serial.print(v[3][0]);
    Serial.println();

#endif

    ControlD1M1(v[0][0], v[0][1]);
    ControlD1M2(v[1][0], v[1][1]);
    ControlD2M1(v[2][0], v[2][1]);
    ControlD2M2(v[3][0], v[3][1]);
}
}

#endif

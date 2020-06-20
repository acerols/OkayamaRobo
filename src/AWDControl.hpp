#include <Arduino.h>
#include <math.h>

const int MOTORNUM = 4;

class AwdControl{
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
	if(dir){
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
	if(dir){
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
    if(speeds > 250)speeds = 250;
    else if(speeds < 0) speeds = 0;
    /* 
    角度に対するＰＷＭ最大出力を決める
    */
    double c = cos(deg2rad(deg));
    double s = sin(deg2rad(deg));
    double t = max(c, s);
    spd = 250 / (1.0 / t);
    double rad = deg * (pi / 180);
    double Y = sin(rad);
    double X = cos(rad);
    int OUT = (
        Y * MV[MN-1][0] * spd +
        X * MV[MN-1][1] * spd
    );
    return OUT;
}

void AwdControl::movefored(void)
{
    int v[4][2] = {0};
    for(int i = 1; i <= MOTORNUM; i++){
        v[i-1][1] = deg2out(90, i);
        if(v[i-1][1] > 0){
            v[i-1][0] = 1;
        }
        else{
            v[i-1][0] = -1;
        }
    }

    ControlD1M1(v[0][0], v[0][1]);
    ControlD1M2(v[1][0], v[1][1]);
    ControlD2M1(v[2][0], v[2][1]);
    ControlD2M2(v[3][0], v[3][1]);
}

void AwdControl::movedir(int deg, int speeds)
{
    int v[4][2] = {0};

    for(int i = 1; i <= MOTORNUM; i++){
        v[i-1][1] = deg2out(deg, i, 250);
        if(v[i-1][1] > 0){
            v[i-1][0] = 1;
        }
        else{
            v[i-1][0] = -1;
        }
    }

    ControlD1M1(v[0][0], v[0][1]);
    ControlD1M2(v[1][0], v[1][1]);
    ControlD2M1(v[2][0], v[2][1]);
    ControlD2M2(v[3][0], v[3][1]);
}
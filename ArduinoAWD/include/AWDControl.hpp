#include <Arduino.h>
#include <math.h>

#include <Connection.hpp>

const int MOTORNUM = 4;

extern Nano nano;

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
    void MControlD1M1(int dir, int sp);
    void MControlD1M2(int dir, int sp);
    void MControlD2M1(int dir, int sp);
    void MControlD2M2(int dir, int sp);

    int16_t pre_P, duty;
    int16_t P, I, D;
    const double dt = 0.1;
    const double KP = 0.5;
    const double  KI = 0.2;
    const double KD = 0.05;

public:
    AwdControl(int d1m1d, int d1m1p, int d1m2d, int d1m2p, int d2m1d, int d2m1p, int d2m2d, int d2m2p);
    void setD1(int m1d, int m1p, int m2d, int m2p);
    void setD2(int m1d, int m1p, int m2d, int m2p);
    void movefored(void);
    void setMD1(int m1d, int m1p, int m2d, int m2p);
    void setMD2(int m1d, int m1p, int m2d, int m2p);
    void movedir(int deg, int speeds);
    void movedir(int x, int y, int speeds);
    //void movedir(int deg, int speeds, int theta); 
    void moveturn(int dir, int speeds);
    void turn_pid(int NowAngle, int TargetAngle, bool enable);
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

void AwdControl::MControlD1M1(int dir, int sp)
{
    sp = abs(sp);
	if(dir == 1){
		digitalWrite(D1M1D, LOW);
		analogWrite(D1M1P, sp);
	}
	else{
		digitalWrite(D1M1D, HIGH);
		analogWrite(D1M1P, 255-sp);
	
	}
}

void AwdControl::MControlD1M2(int dir, int sp)
{
    sp = abs(sp);
	if(dir == 1){
		digitalWrite(D1M2D, LOW);
		analogWrite(D1M2P, sp);
	}
	else{
		digitalWrite(D1M2D, HIGH);
		analogWrite(D1M2P, 255-sp);
	
	}
}

void AwdControl::MControlD2M1(int dir, int sp)
{
    sp = abs(sp);
	if(dir == 1){
		digitalWrite(D2M1D, LOW);
		analogWrite(D2M1P, sp);
	}
	else{
		digitalWrite(D2M1D, HIGH);
		analogWrite(D2M1P, 255-sp);
	
	}
}

void AwdControl::MControlD2M2(int dir, int sp)
{
    sp = abs(sp);
	if(dir == 1){
		digitalWrite(D2M2D, LOW);
		analogWrite(D2M2P, sp);
	}
	else{
		digitalWrite(D2M2D, HIGH);
		analogWrite(D2M2P, 255-sp);
	
	}
}

AwdControl::AwdControl(int d1m1d, int d1m1p, int d1m2d, int d1m2p, int d2m1d, int d2m1p, int d2m2d, int d2m2p)
{
  this->setMD1(d1m1d, d1m1p, d1m2d, d1m2p);
  this->setMD2(d2m1d, d2m1p, d2m2d, d2m2p);
  pre_P = 0;
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

void AwdControl::setMD1(int m1d, int m1p, int m2d, int m2p)
{
  D1M1D = m1d;
  D1M1P = m1p;
  D1M2D = m2d;
  D1M2P = m2p;
  digitalWrite(D1M1D, LOW);
  analogWrite(D1M1P, 0);
  digitalWrite(D1M2D, LOW);
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

void AwdControl::setMD2(int m1d, int m1p, int m2d, int m2p)
{
  D2M1D = m1d;
  D2M1P = m1p;
  D2M2D = m2d;
  D2M2P = m2p;
  digitalWrite(D2M1D, LOW);
  analogWrite(D2M1P, 0);
  digitalWrite(D2M2D, LOW);
  analogWrite(D2M2P, 0);
  /*
  Serial.println("Set");

  Serial.print(D2M1D);
  Serial.print(" ");
  Serial.print(D2M1P);
  Serial.print(" ");
  Serial.print(m1d);
  Serial.print(" ");
  Serial.print(m1p);
  Serial.println(" ");
  */
  
}

const double pi = 3.141592;
static const int MV[4][3] ={
    {1, -1, 1},
    {1, 1, 1},
    {-1, -1, 1},
    {-1, 1, 1},
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

int xy2out(int x, int y, int MN, int speeds)
{
    int vx = x;
    int vy = y;
    
    int OUT = (
        vy * MV[MN-1][0] +
        vx * MV[MN-1][1]
    );
    /*
    Serial.println(vx, DEC);
    Serial.println(vy, DEC);
    Serial.println(OUT, DEC);
    */
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
    MControlD1M1(v[0][0], v[0][1]);
    MControlD1M2(v[1][0], v[1][1]);
    MControlD2M1(v[2][0], v[2][1]);
    MControlD2M2(v[3][0], v[3][1]);

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
}

void AwdControl::movedir(int deg, int speeds)
{
    int v[4][2] = {0};

    if(speeds == 0){
        MControlD1M1(0, 0);
        MControlD1M2(0, 0);
        MControlD2M1(0, 0);
        MControlD2M2(0, 0);
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

    nano.print(v[0][1]);
    nano.print(" ");
    nano.print(v[1][1]);
    nano.print(" ");
    nano.print(v[2][1]);
    nano.print(" ");
    nano.print(v[3][1]);
    nano.println();
    nano.print(v[0][0]);
    nano.print(" ");
    nano.print(v[1][0]);
    nano.print(" ");
    nano.print(v[2][0]);
    nano.print(" ");
    nano.print(v[3][0]);
    nano.println();

    MControlD1M1(v[0][0], v[0][1]);
    MControlD1M2(v[1][0], v[1][1]);
    MControlD2M1(v[2][0], v[2][1]);
    MControlD2M2(v[3][0], v[3][1]);
}

void AwdControl::movedir(int x, int y, int speeds)
{
    int v[4][2] = {0};

    if(speeds == 0){
        MControlD1M1(0, 0);
        MControlD1M2(0, 0);
        MControlD2M1(0, 0);
        MControlD2M2(0, 0);
        return;
    }

    for(int i = 1; i < MOTORNUM+1; i++){
        v[i-1][1] = xy2out(x, y, i, speeds);
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
    MControlD1M1(v[0][0], v[0][1]);
    MControlD1M2(v[1][0], v[1][1]);
    MControlD2M1(v[2][0], v[2][1]);
    MControlD2M2(v[3][0], v[3][1]);
}

/*
void AwdControl::movedir(int deg, int speeds)
{
    double rads = deg2rad(deg);
    int x = (int)cos((double)rads);
    int y = (int)sin((double)rads);
    movedir(x, y, speeds);
    /*
    int v[4][2] = {0};

    if(speeds == 0){
        MControlD1M1(0, 0);
        MControlD1M2(0, 0);
        MControlD2M1(0, 0);
        MControlD2M2(0, 0);
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
    MControlD1M1(v[0][0], v[0][1]);
    MControlD1M2(v[1][0], v[1][1]);
    MControlD2M1(v[2][0], v[2][1]);
    MControlD2M2(v[3][0], v[3][1]);
    
}

*/


int deg2out(int deg, int MN, int speeds, int theta)
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


void AwdControl::moveturn(int dir, int speeds)
{
    int v[4][2] = {0};

    if(dir > 0){
        for(int i = 0; i < MOTORNUM; i++){
            v[i][0] = MV[i][2];
            v[i][1] = speeds;
        }
    }
    else if (dir < 0){
        for(int i = 0; i < MOTORNUM; i++){
            v[i][0] = MV[i][2] * -1;
            v[i][1] = speeds;
        }
    }
    else{
    }
    MControlD1M1(v[0][0], v[0][1]);
    MControlD1M2(v[1][0], v[1][1]);
    MControlD2M1(v[2][0], v[2][1]);
    MControlD2M2(v[3][0], v[3][1]);
}

void AwdControl::turn_pid(int NowAngle, int TargetAngle, bool enable)
{
    int16_t angle = NowAngle + 180;
    int16_t target = TargetAngle + 180;
    P = target - angle;
    I += (int16_t)((double)P * dt);
    D = (int16_t)((double)(P - pre_P) / dt);
    pre_P = P;
    int16_t kp = KP * P;
    int16_t ki = KI * I * 0;
    int16_t kd = KD * D;
    int16_t turnsp = kp + ki + kd;
    if(turnsp > 255)
        turnsp = 255;
    if(turnsp < -255)
        turnsp = -255;

    /*
    nano.print("angle");
    nano.println(angle);
    nano.print("GoalAngel");
    nano.println(target);
    nano.print("P ");
    nano.print(P);
    nano.print(" pre_P ");
    nano.println(pre_P);
    nano.print("kp ");
    nano.println(kp);
    nano.print("I ");
    nano.println(I);
    nano.print("ki ");
    nano.println(ki);
    nano.print("D ");
    nano.println(D);
    nano.print("kd");
    nano.println(kd);
    nano.print("turn speed");
    nano.println(turnsp);
    */
    if(enable){
        moveturn(turnsp, turnsp);
    }
}
#include"zheader.h"

struct regType{
  double kp;
  double ki;
  double kd;
};
void zgetConstants(double *kp, double *ki, double *kd, int *typeRegulator){

  //deklarere hele jævla struckten her
  struct regType P;
  struct regType PI;
  struct regType PD;
  struct regType PID;

  /* Regtype P spesification*/
  P.kp=1.0;
  P.ki=0;
  P.kd=0;
  //regType PI//
  PI.kp=2.0;
  PI.ki=0.5;
  PI.kd=0;
  //regType PD//
  PD.kp=1.0;
  PD.ki=0;
  PD.kd=0.2;
  //regType PID//
  PID.kp=1.0;
  PID.ki=0.2;
  PID.kd=0.31;

  switch (*typeRegulator) {
    case 1 :
        *kp=P.kp;
        *ki=P.ki;
        *kd=P.kd;
    case 2 :
        *kp=PI.kp;
        *ki=PI.ki;
        *kd=PI.kd;
    case 3 :
        *kp=PD.kp;
        *ki=PD.ki;
        *kd=PD.kd;
    case 4 :
        *kp=PID.kp;
        *ki=PID.ki;
        *kd=PID.kd;
    }//eoswitch

}

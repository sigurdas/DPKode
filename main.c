#include"header.h"

int main()
{
  int STARTPOS, refcm;
  double filteredInp, kp, ki, kd;
  CPhidgetInterfaceKitHandle sensor = 0; //Create handels for Phidgets
  CPhidgetServoHandle servo = 0;

  initialize(&kp, &ki, &kd, &STARTPOS, &filteredInp, &sensor, &servo, &refcm);

  loopAndPlot(&kp, &ki, &kd, &STARTPOS, &filteredInp, &sensor, &servo, &refcm);

  closeDelete(sensor, servo);

  return 0;
}//eofmain

#include"zheader.h"

void main()
{
  int STARTPOS;
  double filteredInp, kp, ki, kd;
  CPhidgetInterfaceKitHandle sensor = 0; //Create handels for Phidgets
  CPhidgetServoHandle servo = 0;

  zinitialize(&kp, &ki, &kd, &STARTPOS, &filteredInp, &sensor, &servo);
  CPhidgetServo_setPosition (servo, 0, 125);
  sleep(3);

  loopAndPlot(&kp, &ki, &kd, &STARTPOS, &filteredInp, sensor, servo);

  zcloseDelete(sensor, servo);//Close and Delete phidget handles

  }//eofmain

#include"header.h"

void closeDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo, FILE *fpGNU){


  //Turn servo to zero
  CPhidgetServo_setPosition (servo, 0, 125);
sleep(3);
CPhidgetServo_setPosition (servo, 0, 0);
  //Close resultsfile
  fclose(fpGNU);

  CPhidget_close((CPhidgetHandle)sensor);
  CPhidget_close((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)sensor);

}

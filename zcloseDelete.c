#include"zheader.h"

void zcloseDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo){

  CPhidgetServo_setPosition (servo, 0, 0);

  CPhidget_close((CPhidgetHandle)sensor);
  CPhidget_close((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)sensor);

}

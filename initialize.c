#include"header.h"

void initialize(int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo) {

  //Connect to Potiometer
  CPhidgetInterfaceKit_create(sensor);
  CPhidget_open((CPhidgetHandle)(*sensor), -1);
	CPhidget_waitForAttachment((CPhidgetHandle)(*sensor), 20000);

  //Get startposition of boat, endre portnr.
  CPhidgetInterfaceKit_getSensorValue(*sensor, 0, STARTPOS);

  //set startvalue for filter
  *filteredInp=*STARTPOS;
usleep(200000);
  //Connect to servo
  CPhidgetServo_create(servo);
  CPhidget_open((CPhidgetHandle)(*servo),-1);
  CPhidgetServo_setPosition (*servo, 0, 130);
  printf("\nStarting system\n");
  usleep(2000000);


}

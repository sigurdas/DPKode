#include"zheader.h"

void zinitialize(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo) {

  int typeRegulator;

  //Connect to Potiometer
  CPhidgetInterfaceKit_create(sensor);
  CPhidget_open((CPhidgetHandle)(*sensor), -1);
	CPhidget_waitForAttachment((CPhidgetHandle)(*sensor), 20000);

  //Get startposition of boat
  CPhidgetInterfaceKit_getSensorValue(*sensor, 0, STARTPOS);

  //set startvalue for filter
  *filteredInp=*STARTPOS;

  //Connect to servo
  CPhidgetServo_create(servo);
  CPhidget_open((CPhidgetHandle)(*servo),-1);
  CPhidgetServo_setPosition (*servo, 0, 130);
  printf("\nStarting system\n");
  usleep(2000000);

  printf("Please choose type of regulator:\n");
  printf("Press 1 for Proportional\nPress 2 for Proportonal-Integrate\nPress 3 for Propostional-Derivate\nPress 4 for Proportional-Integrate-Derivate");
  scanf("%d",&typeRegulator);

  zgetConstants(kp, ki, kd, &typeRegulator);

}

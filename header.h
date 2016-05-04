#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<phidget21.h>
#include<ncurses.h>

int pidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double filteredInp, double kp, double ki, double kd);
float getTime(void);
void closeDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo);
int correctPIDOutput(double *pidOut);
void initialize (double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo, int *refcm);
void filterInp(int *inp, double *filteredInp);
void getConstants(double *kp, double *ki, double *kd, int *typeRegulator, char *typeResponse);
void loopAndPlot(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo, int *refcm);

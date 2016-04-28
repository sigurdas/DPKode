#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<phidget21.h>
#include<ncurses.h>

int zpidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double filteredInp, double kp, double ki, double kd);
float gettime(void);
void zcloseDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo);
int correctPIDOutput(double *pidOut);
void zinitialize (double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo);
void filterInp(int *inp, double *filteredInp);
void zgetConstants(double *kp, double *ki, double *kd, int *typeRegulator);
void loopAndPlot(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo);

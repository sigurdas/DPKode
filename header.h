#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<phidget21.h>
#include<ncurses.h>

int pidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double *filteredInp);
float gettime(void);
void closeDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo, FILE *fpGNU);
int correctPIDOutput(double *pidOut);
void initialize (int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo);
void filterInp(int *inp, double *filteredInp);

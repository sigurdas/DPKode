#include"header.h"

//Allows lasterror to be used next itteration
static double lasterror= 0;
double dt, pidOut;

int pidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double *filteredInp)
{
  //Constants
  double kp = 0.9;
  double ki = 0.2;
  double kd = 0.31;

  dt = gettime()-(*t);
  *error = *filteredInp- (*ref);

  //Calculate P,I,D values
  *pValue = kp*(*error);
  *iValue =*iValue + ki*(*error)*dt;
  *dValue = kd*((*error)-lasterror)/dt;

  lasterror = *error;
  pidOut=*pValue+*iValue+*dValue;

  return pidOut;

}

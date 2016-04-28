#include"zheader.h"

//Allows lasterror to be used next itteration
static double lasterror= 0;
double dt, pidOut;

int zpidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double filteredInp, double kp, double ki, double kd)
{

  dt = gettime()-(*t);
  *error = filteredInp- (*ref);

  //Calculate P,I,D values
  *pValue = (kp)*(*error);
  *iValue =*iValue + (ki)*(*error)*dt;
  *dValue = (kd)*((*error)-lasterror)/dt;

  lasterror = *error;
  pidOut=*pValue+*iValue+*dValue;

  return pidOut;

}

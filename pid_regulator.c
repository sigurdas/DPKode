
#include"header.h"

double algout, dt;//refp
//float dt;
//static double i_value;
static double lasterror;
int pid_regulator(int *inp, int *ref, int *startpos, float *t, double *error, double *p_value, double *i_value, double *d_value)
{
  double kp = 2.5;
  double ki = 0.3;
  double kd = 0.2;
  //double refp= (*startpos)-(*ref)*100/27;
  dt = gettime()-(*t);
  *error = (*inp)-(*ref);//refp
  *p_value = kp*(*error);
 *i_value =*i_value + ki*(*error)*dt;
   *d_value = kd*((*error)-lasterror)/dt;

  lasterror = *error;


  algout=*p_value+*i_value+*d_value;
//printf("error: %4.2f, p_value: %4.2f, algout: %4.2f\n", *inp, error, p_value, algout);
//printf(" error: %4.2f, p_value: %4.2f, i_value: %4.2f, d_value: %4.2f, algout: %4.2f\n", error, p_value, i_value, d_value, algout);

 //return algout, error, p_value, i_value, d_value;
return algout;

}

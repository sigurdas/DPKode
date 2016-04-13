#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<phidget21.h>
#include<ncurses.h>

int pid_regulator(int *inp, int *ref, int *startpos, float *t, double *error, double *p_value, double *i_value, double *d_value);
float gettime(void);

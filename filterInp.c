#include"zheader.h"

void filterInp(int *inp, double *filteredInp) {
  double beta = 0.8;

  *filteredInp= *filteredInp - beta*((*filteredInp) -(*inp));
}

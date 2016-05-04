#include"header.h"

/*
----------------------------------------------------------------------------
DP                            Subroutine                         filterInp
----------------------------------------------------------------------------

Hensikt :
Filtrere data fra potiometeret
Metode :
Sende rådataen gjennom et enkelt IIR-filter

............................................................................

INTERNE VARIABLER:                         Innhold/Beskrivelse
beta                                  Konstant for grad av filtrering

----------------------------------------------------------------------------
Programmert av                                         Sigurd Aurvaag Soerum
Date                                                              03.05.2016
****************************************************************************
*/

void filterInp(int *inp, double *filteredInp) {
  double beta = 0.9;

  *filteredInp= *filteredInp - beta*((*filteredInp) -(*inp));
}

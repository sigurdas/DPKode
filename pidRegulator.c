#include"header.h"

/*
------------------------------------------------------------------------------
DP                            Subroutine                          pidRegulator
-----------------------------------------------------------------------------

Hensikt :
 Beregne pådraget for systemet

Metode :
 Benytte avviket mellom posisjonen og referansen, sammen med endringen i
 tid siden forrige kall av funskjonen, til å beregne proporsjonal, derivat
 og integraldelen av pådraget.

..............................................................................

FUNKSJONER:                             Innhold/Beskrivelse
 getTime                     Henter ut tiden

RETURNERER:
 pidOut                      Beregnet pådrag

INTERNE VARIABLER:
 lasterror                   Inneholder forrige feil, blir benyttet neste kall
 dt                          Endring i tid siden forrige kall av funksjonen

------------------------------------------------------------------------------
Programmert av                                           Sigurd Aurvaag Soerum
Date                                                                28.04.2016
******************************************************************************

*/

static double lasterror= 0;
double pidOut;
float dt;

int pidRegulator( int *ref, float *t, double *error, double *pValue, double *iValue, double *dValue, double filteredInp, double kp, double ki, double kd)
{

  dt = getTime()-(*t);
  *error = filteredInp- (*ref);

  //Calculate P,I,D values
  *pValue = (kp)*(*error);
  *iValue =*iValue + (ki)*(*error)*dt;
  *dValue = (kd)*((*error)-lasterror)/dt;

  lasterror = *error;
  pidOut=*pValue+*iValue+*dValue;

  return pidOut;

}

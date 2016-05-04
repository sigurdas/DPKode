#include"header.h"

/*
--------------------------------------------------------------------------
DP                          Subroutine                  correctPIDOutput
--------------------------------------------------------------------------

Hensikt :
 Korrigere beregnet pådrag innenfor servoens funksjonsrammer
Metode :
 Filtrere pådraget innenfor rammene av målt servofunksjon

...........................................................................

RETURNERER:                                Innhold/Beskrivelse
 setservo                             Posisjon for servo

----------------------------------------------------------------------------
Programmert av                                         Sigurd Aurvaag Soerum
Date                                                              03.05.2016
****************************************************************************
*/

int correctPIDOutput(double *pidOut){

   int setservo;

   if(*pidOut+105>=195){
     setservo=195;
   }
   else if(*pidOut<=0){
     setservo=105;
   }
   else {
     setservo=*pidOut+105;
   }
   return setservo;
}

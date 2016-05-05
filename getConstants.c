#include"header.h"

/*
--------------------------------------------------------------------------
DP                           Subroutine                      getConstants
--------------------------------------------------------------------------

Hensikt :
 Definere konstanter for bruk i PID-regulering, basert på brukers valg

Metode :
 Hente ut forhåndsbestemte sett med konstanter basert på brukers valg

.............................................................................

FUNKSJONER:                               Innhold/Beskrivelse
 if                                Logisk test av en påstand
 switch                            Velger forskjellige caser basert på argument

INTERNE VARIABLER:
 fastResponse                      Struct med konstanter for forskjellige
                                          regulatorer
 noOvershoot                       Struct med konstanter for forskjellige
                                          regulatorer

-----------------------------------------------------------------------------
Programmert av                                          Sigurd Aurvaag Soerum
Date                                                               28.04.2016
*****************************************************************************
*/
struct fastResponse{
  double kp;
  double ki;
  double kd;
};
struct noOvershoot{
  double kp;
  double ki;
  double kd;
};
void getConstants(double *kp, double *ki, double *kd, int *typeRegulator, char *typeResponse){

  struct fastResponse fastResponseP, fastResponsePI, fastResponsePD, fastResponsePID;
  struct noOvershoot noOvershootP, noOvershootPI, noOvershootPD, noOvershootPID;

  /* Regtype P spesification*/
  fastResponseP.kp=0.7;
  fastResponseP.ki=0;
  fastResponseP.kd=0;
  //regType PI//
  fastResponsePI.kp=0.375;
  fastResponsePI.ki=0.13;
  fastResponsePI.kd=0;
  //regType PD//
  fastResponsePD.kp=3.0;
  fastResponsePD.ki=0;
  fastResponsePD.kd=1.1;
  //regType PID//
  fastResponsePID.kp=1.8;
  fastResponsePID.ki=0.2;
  fastResponsePID.kd=0.8;

  /* Regtype P spesification*/
  noOvershootP.kp=0.6;
  noOvershootP.ki=0;
  noOvershootP.kd=0;
  //regType PI//
  noOvershootPI.kp=0.375;
  noOvershootPI.ki=0.152;
  noOvershootPI.kd=0;
  //regType PD//
  noOvershootPD.kp=1.32;
  noOvershootPD.ki=0;
  noOvershootPD.kd=0.501;
  //regType PID//
  noOvershootPID.kp=0.6;
  noOvershootPID.ki=0.2;
  noOvershootPID.kd=0.16;

  if (*typeResponse=='y') {
    switch (*typeRegulator) {
      case 1:
          *kp=fastResponseP.kp;
          *ki=fastResponseP.ki;
          *kd=fastResponseP.kd;
          break;
      case 2:
          *kp=fastResponsePI.kp;
          *ki=fastResponsePI.ki;
          *kd=fastResponsePI.kd;
          break;
      case 3:
          *kp=fastResponsePD.kp;
          *ki=fastResponsePD.ki;
          *kd=fastResponsePD.kd;
          break;
      case 4:
          *kp=fastResponsePID.kp;
          *ki=fastResponsePID.ki;
          *kd=fastResponsePID.kd;
          break;
      }//eoswitch
    }//eoif
    else {
      switch (*typeRegulator) {
        case 1:
            *kp=noOvershootP.kp;
            *ki=noOvershootP.ki;
            *kd=noOvershootP.kd;
            break;
        case 2:
            *kp=noOvershootPI.kp;
            *ki=noOvershootPI.ki;
            *kd=noOvershootPI.kd;
            break;
        case 3:
            *kp=noOvershootPD.kp;
            *ki=noOvershootPD.ki;
            *kd=noOvershootPD.kd;
            break;
        case 4:
            *kp=noOvershootPID.kp;
            *ki=noOvershootPID.ki;
            *kd=noOvershootPID.kd;
            break;
        }//eoswitch
    }//eoelse

}//eofuction

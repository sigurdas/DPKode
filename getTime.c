#include"header.h"

/*
--------------------------------------------------------------------------
 DP                           Subroutine                         getTime
--------------------------------------------------------------------------

Hensikt :
 Hente ut tid

Metode :
 Finner tiden siden systemstart

............................................................................

FUNKSJONER:                                  Innhold/Beskrivelse
 clock_gettime                             Henter ut tiden i formen definert

RETURNERER:
 t                                         Tiden siden systemstart i sekunder
                                                  med nanosekunder
INTERNE VARIABLER:
 timespec tid                              Struct som huser tiden i sek og
                                                       nanosekunder

------------------------------------------------------------------------------
Programmert av                                           Sigurd Aurvaag Soerum
Date                                                                03.05.2016
******************************************************************************
*/

struct timespec tid;

float getTime(void){
    float t;

    //Gets time in seconds and nanoseconds, placed in struct
    //Monotonic gets time from system start, to avoid sudden jumps in time
    clock_gettime(CLOCK_MONOTONIC, &tid);
    t= tid.tv_sec + pow(10, -9)*tid.tv_nsec;
  return t;
  }

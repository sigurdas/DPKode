#include"header.h"

/*
-----------------------------------------------------------------------------
 DP                          Subroutine                           initalize
-----------------------------------------------------------------------------

Hensikt :
 Gjøre programmet klart for posisjonering

Metode :
 Koble til phidgets og bestemme hvilken type regulator bruker ønsker

  ...........................................................................

FUNKSJONER:                                     Innhold/Beskrivelse
 CPhidgetInterfaceKit_create            Lager en kobling til potiometeret
 CPhidgetServo_create                   Lager en kobling til servoen
 CPhidget_open                          Åpner nevnt kobling
 CPhidgetInterfaceKit_getSensorValue    Henter ut info fra Potiometeret
 CPhidgetServo_setPosition              Sender posisjon til servoen
 CPhidget_waitForAttachment             Venter på tilkobling, returnerer 0
                                           hvis vellykket, 13 ellers
 getConstants                           Henter ut konstantene til PID-
                                           regulering avhengig av brukers valg

INTERNE VARIABLER:
typeRegulator                           Hvordan type regulator bruker ønsker
typeResponse                            Hvordan type respons bruker ønsker

------------------------------------------------------------------------------
Programmert av                                           Sigurd Aurvaag Soerum
Date                                                                03.05.2016
******************************************************************************
*/
void initialize(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo, int *refcm) {

  int typeRegulator;
  char typeResponse;

  //Connect to Potiometer
  CPhidgetInterfaceKit_create(sensor);
  CPhidget_open((CPhidgetHandle)(*sensor), -1);
	if (CPhidget_waitForAttachment((CPhidgetHandle)(*sensor), 20000) != 0) {
	  printf("Potensiometer not connected\n");
	}


  //Get startposition of boat
  CPhidgetInterfaceKit_getSensorValue(*sensor, 0, STARTPOS);//

  //set startvalue for filter
  *filteredInp=*STARTPOS;

  //Connect to servo
  CPhidgetServo_create(servo);
  CPhidget_open((CPhidgetHandle)(*servo),-1);
  if (CPhidget_waitForAttachment((CPhidgetHandle)(*servo), 20000) != 0) {
	  printf("Servo not connected\n");
	}

  CPhidgetServo_setPosition (*servo, 0, 125);//start engine
  printf("\nStarting system\n");
  sleep(1);

  printf("Is the system allowed overshoot?\ny/n\n");
  scanf("%s", &typeResponse);


  printf("Please choose type of regulator:\n");
  printf("Press 1 for Proportional\nPress 2 for Proportonal-Integrate\nPress 3 for Propostional-Derivate\nPress 4 for Proportional-Integrate-Derivate\n");
  scanf("%d",&typeRegulator);

  getConstants(kp, ki, kd, &typeRegulator, &typeResponse);

  printf("\nEnter wanted position from current position:\n");//Ask user for referance
  scanf("%d",refcm);
}

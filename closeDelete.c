#include"header.h"

/*
---------------------------------------------------------------------------
DP                              Subroutine                     closeDelete
---------------------------------------------------------------------------

Hensikt :
Skru av og koble fra Phidgets
Metode :
Skru av servo og slette koblinger til Phidgets

............................................................................

FUNKSJONER:                              Innhold/Beskrivelse
CPhidgetServo_setPosition            Sender posisjon til servoen
CPhidget_close                       Stenger kobling til Phidget
CPhidget_delete                      Sletter kobling til Phidget
-----------------------------------------------------------------------------
Programmert av                                          Sigurd Aurvaag Soerum
Date                                                               28.04.2016
*****************************************************************************
*/
void closeDelete (CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo){

  CPhidgetServo_setPosition (servo, 0, 0);

  CPhidget_close((CPhidgetHandle)sensor);
  CPhidget_close((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)sensor);

  printf("\nSystem Closed\n");
}

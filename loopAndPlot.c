#include"header.h"

/*
--------------------------------------------------------------------------
DP                          Subroutine                        loopAndPlot
--------------------------------------------------------------------------

Hensikt :
 Løkke posisjoneringen til bruker velger stopp, og plotte resultatet

Metode :
 Evig while-løkke oppdaterer posisjon og pådrag til bruker sender inn
 stoppsignalet.

.........................................................................

FUNKSJONER:                           Innhold/Beskrivelse
 fopen                        Åpner fil for skriving
 getTime                      Henter ut tiden
 usleep                       Vente i n mikrosekunder
 initscr                      Starte ncurses modus
 cbreak                       Input fra bruker blir umiddelbart tilgjengelig
                                  for programmet

 noecho                       Ikke vis brukers input
 printw                       Printf i ncurses modus
 timeout(0)                   Ikke stopp programmet for å vente på brukers
                                  input

 CPhidgetInterfaceKit_getSensorValue
                              Henter ut info fra Potiometeret

 filteredInp                  Filtrerer posisjonen fra potiometeret
 pidRegulator                 Beregner pådraget
 correctPIDOutput             Begrenser pådraget innenfor servoens mulige
                                      handlingsrom

 CPhidgetServo_setPosition    Sender posisjon til servoen
 fprintf                      Skriver til fil
 getch                        Ta inn tastetrykk fra bruker
 endwin                       Avslutt ncurses modus
 timeout(-1)                  Ber programmet vente til bruker har skrevet
 getstr                       Ta inn streng fra bruker
 strtol                       Konverterer streng til tall
 fclose                       Stenger filpeker
 system("gnuplot -p 'GNUcmd.gp'")
                              Sender kommandoen om å plotte i gnuplot ved bruk
                              av kommandoene i GNUcmd.gp, ut av programmet
                                     til terminal.

INTERNE VARIABLER:
 stop                         Brukerinput
 refstr                       Streng for input fra bruker, til oppdatering
                                      av posisjon

 ptr                          Delen av strengen som er bokstaver
 ref                          Referansen i potiometerskala
 inp                          Posisjon fra potiometeret
 setservo                     Posisjon til servoen
 pidOut                       Beregnet pådrag
 error                        Avvik mellom referansen og posisjonen
 pValue                       Proporsjonaldelen av pådraget
 iValue                       Integraldelen av pådraget
 dValue                       Derivatdelen av pådraget
 t                            Tiden siden systemstart
 STARTTID                     Systemtiden ved start av posisjonering

------------------------------------------------------------------------------
Programmert av                                           Sigurd Aurvaag Soerum
Date                                                                03.05.2016
*******************************************************************************
*/

void loopAndPlot(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle *sensor, CPhidgetServoHandle *servo, int *refcm)
{

char stop, refstr[2], *ptr;
int ref , inp, setservo;
double pidOut, error, pValue, iValue, dValue;
float  t = 0, STARTTID = 0;


FILE *fpGNU;//Open file for datalogging
fpGNU = fopen("GNUres.dat", "w");

t = getTime();//Aquire time
usleep(1000);
STARTTID = getTime();
initscr();//Start ncurses mode
cbreak();// Disable line buffering
noecho();
printw("Press q or Q to end positioning, or press p to give new position from origin.\n");//Use printw in ncurses mode

 while (1) {

   timeout(0);//Set waiting time for keystrokes to zero
   ref= *STARTPOS-(*refcm)*100/27;//Calculate true referance from referance given in centimeters

   CPhidgetInterfaceKit_getSensorValue(*sensor, 0, &inp);//Get position from potiometer

   filterInp(&inp, filteredInp);

   pidOut=pidRegulator(&ref, &t, &error, &pValue, &iValue, &dValue, *filteredInp, *kp, *ki, *kd); //calculate correction in PID controller

   setservo = correctPIDOutput(&pidOut);

   CPhidgetServo_setPosition (*servo, 0, setservo);

   t = getTime();//Update time

   fprintf(fpGNU,"%f %f %f %d %f %f %f %d %d\n", t-STARTTID, error, pidOut, inp, pValue, iValue, dValue, setservo, *refcm);//Print results to resultsfile

   stop = getch();//Check if user sends stop signal
     if(stop == 'q'){
            endwin();
            printf("\nStopping\n");
            break;

     }//eo if
          else if(stop == 'p') {
            printf("\nEnter new Pos\n");
            timeout(-1);//wait til user types position
            getstr(refstr);
            *refcm=strtol(refstr,&ptr, 10);
     }

  usleep(10000);
  }//end of while

fclose(fpGNU);
system("gnuplot -p 'GNUcmd.gp'");//Plot results in gnuplot

}//eofunction

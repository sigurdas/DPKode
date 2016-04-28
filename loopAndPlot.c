#include"zheader.h"

void loopAndPlot(double *kp, double *ki, double *kd, int *STARTPOS, double *filteredInp, CPhidgetInterfaceKitHandle sensor, CPhidgetServoHandle servo)
{

char stop, refstr[2], *ptr;
int refcm, ref , inp;
double pidOut, error, pValue, iValue, dValue, setservo;
float  t = 0, STARTTID = 0;


FILE *fpGNU;//Open file for datalogging
fpGNU = fopen("GNUres.dat", "w");

printf("\nEnter wanted position from current position:\n");//Ask user for referance
scanf("%d",&refcm);




t = gettime();//Aquire time
STARTTID = gettime();
initscr();//Start ncurses mode
cbreak();// Disable line buffering
noecho();
printw("Press q or Q to end positioning, or press p to give new position from origin.\n");//Use printw in ncurses mode

 while (1) {

   timeout(0);//Set waiting time for keystrokes to zero
   ref= *STARTPOS-refcm*100/27;//Calculate true referance from referance given in centimeters

   CPhidgetInterfaceKit_getSensorValue(sensor, 0, &inp);//Get position from potiometer

   filterInp(&inp, filteredInp);

   pidOut=zpidRegulator(&ref, &t, &error, &pValue, &iValue, &dValue, *filteredInp, *kp, *ki, *kd); //calculate correction in PID controller

   setservo = correctPIDOutput(&pidOut);

   CPhidgetServo_setPosition (servo, 0, setservo);//Set servo

   t = gettime();//Update time

   fprintf(fpGNU,"%f %f %f %d %d %f %f %f %f %d\n", t-STARTTID, error, pidOut, inp, ref, pValue, iValue, dValue, setservo, refcm);//Print results to resultsfile

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
          refcm=strtol(refstr,&ptr, 10);
        }

  usleep(30000);  //"Wait for 0.1 sec//100000
  }//end of while

fclose(fpGNU);
system("gnuplot -p 'GNUcmd.gp'");//Plot results in gnuplot
}//eofunction

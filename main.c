#include"header.h"

void main()
{
  int startpos, refcm, ref , inp;//legg til counter
  char stop;
  double algout, error, p_value,i_value, d_value, setservo;
  float dt = 0, t = 0, starttid;//legg til starttime

 FILE *fpGNU;
 fpGNU = fopen("GNUres.dat", "w");
    if(fpGNU==NULL){
        printf("FILE ERROR\n");
          }

  CPhidgetInterfaceKitHandle sensor = 0;
  CPhidgetServoHandle servo = 0;

  CPhidgetInterfaceKit_create(&sensor);
  CPhidget_open((CPhidgetHandle)sensor, -1);
	CPhidget_waitForAttachment((CPhidgetHandle)sensor, 20000);

  CPhidgetInterfaceKit_getSensorValue(sensor, 0, &startpos);

  CPhidgetServo_create(&servo);
  CPhidget_open((CPhidgetHandle)servo,-1);


  printf("Enter wanted position from current position, startpos: %d\n", startpos);
    scanf("%d",&refcm);
   //ref= startpos-refcm*100/27;


   t = gettime();
   starttid = gettime();

//fprintf(fpGNU,"time error algout inp ref p_value i_value d_value setservo\n");
initscr();//start ncurses mode
timeout(0);//venter ikke på at man skriver
cbreak();// slipp igjennom cmds som ctrl-c

printw("Press q or Q to end positioning, or p to enter new pos\n");


 while (1) { //!kbhit()


        ref= startpos-refcm*100/27;


        CPhidgetInterfaceKit_getSensorValue(sensor, 0, &inp);
        algout=pid_regulator(&inp, &ref, &startpos, &t, &error, &p_value, &i_value, &d_value);
        //printf("startpos: %d, inp= %d, algout: %d \r ",startpos, inp, algout);

        //gjøre negativ algout proposjonal,dvs hvis den passerer på 190 la neste verdi være 180ish
              if(algout<0 && algout>=-62) {
                      setservo=195+algout;
                      }
                      else if(algout+132>=195){
                        setservo=195;
                      }
                      else if(algout<=-63){
                        setservo=132;
                      }
                      else {
                        setservo=algout+132;
                      }

        CPhidgetServo_setPosition (servo, 0, setservo);

        t = gettime();



        fprintf(fpGNU,"%f %f %f %d %d %f %f %f %f\n", t-starttid, error, algout, inp, ref, p_value, i_value, d_value, setservo);

        stop = getch();
        if(stop == 'q' || stop == 'Q'){
                  printf("\nStopping\n");
                  break;
                }//eo if
                //else if(stop == 'p'){
                    //  printf("Enter new Pos\n");
                    //  scanw("%d",&refcm);

                //  }//eo if
        // switch(stop) {
          //  case 'q' :
            //          printf("\nStopping\n");
              //      break;
                //      break;
          //  case 'p' :
                  //    printw("Enter new pos\n");
                  //    scanw("%d",&refcm);


        usleep(100000);
  }//end of while
      endwin();//end ncurses

    CPhidgetServo_setPosition (servo, 0, 127);//skru av motor
    fclose(fpGNU);
    system("gnuplot -p 'GNUcmd.gp'");



  CPhidget_close((CPhidgetHandle)sensor);
  CPhidget_close((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)servo);
  CPhidget_delete((CPhidgetHandle)sensor);

  printf("Alt stengt, lukker....\n");


}//eofmain

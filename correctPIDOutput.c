#include"zheader.h"

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

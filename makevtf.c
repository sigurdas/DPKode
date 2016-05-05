#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<time.h>
/*
------------------------------------------------------------------------------
DP                            Subroutine                            makevtf
-----------------------------------------------------------------------------
Hensikt :
 Lage kjørbar vtf-fil av resultatene fra posisjoneringen.
Metode :
 Konvertere data fra GNUres.dat til VTFres.vtf
..............................................................................
FUNKSJONER:                             Innhold/Beskrivelse
 fscanf                      Henter ut data fra fil
 feof                        Skjekk om man har nådd slutten av filen
------------------------------------------------------------------------------
Programmert av                                           Sigurd Aurvaag Soerum
Date                                                                28.04.2016
******************************************************************************
*/
int main(void){
FILE *fpGNU =fopen("/home/sig/datamet/GNUres.dat","r");
FILE *fpVTF =fopen("/home/sig/datamet/VTFres.vtf","w");
int  inp, ref, pos, counter=1, i, refmarker, startpos;
double tid, p_value, i_value, d_value, algout, error, setservo;

fscanf(fpGNU, "%lf %lf %lf %d %d %lf %lf %lf %lf",&tid,&error,&algout,&inp, &ref, &p_value, &i_value, &d_value, &setservo);

startpos=inp;
refmarker=((startpos-ref)*27/100)+5;

fprintf(fpVTF,"*VTF-1.00\n\n");

//Nodes for boat
fprintf(fpVTF,"*NODES 1\n");
fprintf(fpVTF,"-7 5 5\n");
fprintf(fpVTF,"7 5 5\n");
fprintf(fpVTF,"5 5 -5\n");
fprintf(fpVTF,"-5 5 -5\n");
fprintf(fpVTF,"-9 25 5\n");
fprintf(fpVTF,"9 25 5\n");
fprintf(fpVTF,"-9 25 -5\n");
fprintf(fpVTF,"9 25 -5\n");
fprintf(fpVTF,"0 65 5\n");
fprintf(fpVTF,"0 45 -5 \n\n");


//Nodes for waterplane
fprintf(fpVTF,"*NODES 2\n");
fprintf(fpVTF,"-25 0 0\n");
fprintf(fpVTF,"25 0 0\n");
fprintf(fpVTF,"-25 110 0\n");
fprintf(fpVTF,"25 110 0\n\n");

//Nodes for referance marker
fprintf(fpVTF,"*NODES 3\n");

fprintf(fpVTF,"-25 %d 1\n", refmarker);
fprintf(fpVTF,"-25 %d -1\n", refmarker);
fprintf(fpVTF,"25 %d 1\n", refmarker);
fprintf(fpVTF,"25 %d -1\n\n", refmarker);

//Element 1 Boat
fprintf(fpVTF,"*ELEMENTS 1\n");
fprintf(fpVTF,"%%NODES #1\n");
fprintf(fpVTF,"%%HEXAHEDRONS\n");
fprintf(fpVTF,"4 3 8 7 1 2 6 5\n\n");
fprintf(fpVTF,"%%PENTAHEDRONS\n");
fprintf(fpVTF,"8 10 7 6 9 5\n\n");


//Element 2 Waterplane
fprintf(fpVTF,"*ELEMENTS 2\n");
fprintf(fpVTF,"%%NODES #2\n");
fprintf(fpVTF,"%%QUADS\n");
fprintf(fpVTF,"1 2 4 3\n\n");

//Element 3 reference marker
fprintf(fpVTF,"*ELEMENTS 3\n");
fprintf(fpVTF,"%%NODES #3\n");
fprintf(fpVTF,"%%QUADS\n");
fprintf(fpVTF,"2 4 3 1\n\n");

//View geometry
fprintf(fpVTF,"*GLVIEWGEOMETRY 1\n");
fprintf(fpVTF,"%%ELEMENTS\n");
fprintf(fpVTF,"1,2,3\n\n");


  while (1){

          if( feof(fpGNU) ) {
              break;
            }//eo if

        //Calculate position of boat in cm
        pos=(startpos-inp)*27/100;

            //Print Results
            fprintf(fpVTF,"*RESULTS %d\n",counter);
            fprintf(fpVTF,"%%DIMENSION 3\n");
            fprintf(fpVTF,"%%PER_NODE #1\n");
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n",pos);
            fprintf(fpVTF,"0, %d, 0\n\n",pos);


        counter= counter+1;

        fscanf(fpGNU, "%lf %lf %lf %d %d %lf %lf %lf %lf",&tid,&error,&algout,&inp, &ref, &p_value, &i_value, &d_value, &setservo);

      }//eo while


fprintf(fpVTF,"*GLVIEWVECTOR 1\n");
fprintf(fpVTF,"%%NAME \"POSITION\" \n\n");

      //Print steps
      for(i=1; i<counter;i++){
          fprintf(fpVTF,"%%STEP %d\n %d\n",i,i);
        }//eo if

//Close filepointers
fclose(fpGNU);
fclose(fpVTF);

return 0;

}

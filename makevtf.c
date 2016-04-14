#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<time.h>

int main(void){
FILE *fpGNU =fopen("/home/sig/datamet/GNUres.dat","r");
FILE *fpVTF =fopen("/home/sig/datamet/VTFres.vtf","w");
int  inp, ref, counter=1,i;
double tid, p_value, i_value, d_value, algout, error, setservo;

fscanf(fpGNU, "%lf %lf %lf %d %d %lf %lf %lf %lf",&tid,&error,&algout,&inp, &ref, &p_value, &i_value, &d_value, &setservo);
fprintf(fpVTF,"*VTF-1.00\n\n");
//prøv 2D først
fprintf(fpVTF,"*NODES 1\n");
fprintf(fpVTF,"0. 0. 0.\n20. 0. 0.\n10. 20. 0.\n\n");//geometri, nodes
fprintf(fpVTF,"*NODES 2\n");//geometri ref
fprintf(fpVTF,"-50 %d 0.\n50 %d 0.\n\n", ref, ref);//geometri

fprintf(fpVTF,"*ELEMENTS 1\n%%NODES #1\n%%TRIANGLES\n1 2 3\n\n");
fprintf(fpVTF,"*ELEMENTS 2\n%%NODES #2 \n%%BEAMS\n1 2\n\n");
fprintf(fpVTF,"*GLVIEWGEOMETRY 1\n%%ELEMENTS\n1,2\n\n");

//for å lese fra fil
while (1){
  if( feof(fpGNU) ) {
    break;
  }

fprintf(fpVTF,"*RESULTS %d\n",counter);
fprintf(fpVTF,"%%DIMENSION 2\n");
fprintf(fpVTF,"%%PER_NODE #1\n");
fprintf(fpVTF,"0, %d\n",inp);
fprintf(fpVTF,"0, %d\n",inp);
fprintf(fpVTF,"0, %d\n\n",inp);
counter= counter+1;
fscanf(fpGNU, "%lf %lf %lf %d %d %lf %lf %lf %lf",&tid,&error,&algout,&inp, &ref, &p_value, &i_value, &d_value, &setservo);
}//eo while


fprintf(fpVTF,"*GLVIEWVECTOR 1\n");
fprintf(fpVTF,"%%NAME \"POSITION\" \n");


for(i=1; i<counter;i++){
fprintf(fpVTF,"%%STEP %d\n %d\n",i,i);
}

fclose (fpGNU);
fclose(fpVTF);
return 0;
}
// ide: definere(og måle) tanken, ha den som boks, ha vannnivå oppi,+ hoveddim
//på båt. gjøre om error til feil i cm, og ha et plan som viser refpkt.

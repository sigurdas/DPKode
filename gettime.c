#include"header.h"

//Declare timespec struct
struct timespec tid;


float gettime(void){
    float t;

    //Gets time in seconds and nanoseconds, placed in struct
    //Monotonic gets time from system start, to avoid sudden jumps in time
    clock_gettime(CLOCK_MONOTONIC, &tid);
    t= tid.tv_sec + pow(10, -9)*tid.tv_nsec;
  return t;
  }

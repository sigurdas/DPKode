//#pragma once

#include"header.h"

struct timespec tiem;


float gettime(void){
  float ti;
clock_gettime(CLOCK_MONOTONIC, &tiem);
ti= tiem.tv_sec + pow(10, -9)*tiem.tv_nsec;
 return ti;
}

//fikse tiem, forklare hvorfor MONOTONIC, hva som kommer ut

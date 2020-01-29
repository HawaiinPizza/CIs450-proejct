#include<queue>
#include<iostream>
#include<algorithm>
#include "Main.h"

// Process @3: 2 5 8 7 4
// Process @5: 4
// Process @6: 8 2 10 2 7 5 6


int main(){
  Processor War;
  int atemp1[5]={2,5,8,7,4};
  int atemp2[7]={8,2,10,2,7,5,6};
  Process ptemp1(atemp1, 5, 1);
  Process ptemp2(atemp2, 7, 2);
  Processor CPU;
  CPU.push(ptemp2);
  CPU.push(ptemp1);

  int i=0;
  bool io_idle=true;
  bool cpu_idle=true;

  while(i<25){
    // JObs arrived
    printf("Time:%d\t", i);
    
    // IO Idle
    if(io_idle){
      
    }
    else{
    }

    //CPU Idle
    if(cpu_idle){
    }
    else{
    }


    printf("\n");
    i++;

  }
  
}

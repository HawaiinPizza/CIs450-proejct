#include<queue>
#include<iostream>
#include<algorithm>
#include "Main.h"

// Process @3: 2 5 8 7 4
// Process @5: 4
// Process @6: 8 2 10 2 7 5 6


int main(){
  Processor War;
  int s1=3;
  int atemp1[5]={2,5,8,7,4};
  int atemp2[7]={8,2,10,2,7,5,6};
  int atemp3[1]={4};
  Process ptemp1(atemp1, 5, 1, 3);
  Process ptemp3(atemp2, 7, 2, 6);
  Process ptemp2(atemp3, 1, 3, 5);
  Processor CPU;
  queue<Process> PPtemp;
  PPtemp.push(ptemp1);
  PPtemp.push(ptemp2);
  PPtemp.push(ptemp3);
  int Quant=3;

  int i=0;
  bool io_idle=true;
  bool cpu_idle=true;

  while(i<100){
    printf("Time:%d\t", i);
    // JObs arrived
    if(PPtemp.front().arrTime==i){
      CPU.push(PPtemp.front());
      printf("Job %i has arrived\t", PPtemp.front().id);
      PPtemp.pop();
    }


    
    /* IO Idle*/
    if(io_idle){

      if(CPU.empty(false)){
	printf("IO is  idle\t");
      }
      else{
	CPU.setJob(false);
	printf("New IO job of %d\t", CPU.IO.id);
	io_idle=false;
      }
      
    }
    else{
      --CPU;
      printf("IO Time %d ID %d\t", CPU.IO.timeleft, CPU.IO.id);
      if(CPU.IO.State==IO_DONE){
	io_idle=true;
	CPU.PopBack(false);
	printf("IO Done\t");
      }
    }

    printf(":\t\t");
    /*CPU Idle*/
    if(cpu_idle){
      if(CPU.empty()){
	printf("CPU is idle\t");

      }
      else{
	CPU.setJob();
	printf("New CPU job of %d\t", CPU.CPU.id);
	cpu_idle=false;

      }
    }
    else{
      CPU--;
      printf("CPU Time %d ID %d\t", CPU.CPU.timeleft, CPU.CPU.id);
      if(CPU.CPU.State==IO_REQUEST || CPU.CPU.timeleft == 0){
	cpu_idle=true;
	CPU.PopBack();
	printf("CPU Done\t");
      }
      else if (CPU.CPU.timerun>=Quant){
	cpu_idle=true;
	CPU.Premeted();
	printf("CPU IS PREMETD\t");
      }
    }


    printf(":\t");
    // Print contents of readyqueue
    //CPU.print();
    

    printf("\n");
    i++;

  }
  
}

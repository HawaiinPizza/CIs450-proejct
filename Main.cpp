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
  int atemp2[1]={4};
  int atemp3[7]={8,2,10,2,7,5,6};
  Process ptemp1(atemp1, 5, 1, 3);
  Process ptemp2(atemp2, 1, 2, 5);
  Process ptemp3(atemp3, 7, 3, 7);
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
    bool print=true;
    printf("Time:%d\t", i);
    // JObs arrived
    if(PPtemp.front().arrTime==i){
      print=false;
      CPU.push(PPtemp.front());
      printf("\tJob %i arrives\t", PPtemp.front().id);
      PPtemp.pop();
    }
    if(print)
      printf("\t\t\t");
    
    /* IO Idle #00FF00*/
    if(io_idle){
      //Ready queue is empty
      if(CPU.empty(false)){
	printf("IO is idle/empty");
      }
      else{
	if(CPU.setJob(false)){
	  printf("Adding job to IO %d:%d %d", CPU.IO.timeleft, CPU.IO.id, CPU.size(false));
	    io_idle=false;
	}
	else{
	  printf("Unable to add job to IO");
	}
      }
    }
    else{
      --CPU;
      printf("Run IOjob %d %d\t", CPU.IO.timeleft, CPU.IO.id);
      if(CPU.IO.State==IO_DONE){
	printf(" IO DONE");
	io_idle=true;
	CPU.Back(false);
      }
    }

    printf("\t");

    /*CPU Idle #FF0000*/
    if(cpu_idle){
      //Ready queue is empty
      if(CPU.empty()){
	printf("CPU is idle/empty");
      }
      else{
	if(CPU.setJob()){
	  printf("Adding job to CPU %d:%d %d", CPU.CPU.timeleft,CPU.CPU.id, CPU.size(false));
	    cpu_idle=false;
	}
	else{
	  printf("Unable to add job to CPU");
	}
      }
    }
    else{
      CPU--;
      printf("Run CPU %d %d", CPU.CPU.timeleft, CPU.CPU.id);
      if(CPU.CPU.State==IO_REQUEST){
	printf("\tIO Request");
	cpu_idle=true;
	CPU.Back();
      }
      else if(CPU.CPU.timerun>=Quant){
	printf("\tPremetd");
	cpu_idle=true;
	CPU.Premeted();
      }
    }
    // Print contents of readyqueue
    //CPU.print();
    

    printf("\n");
    i++;

  }
  
}

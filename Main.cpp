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
    printf("Time:%d\t", i);
    // JObs arrived
    if(PPtemp.front().arrTime==i){
      CPU.push(PPtemp.front());
      printf("Job %i has arrived\t", PPtemp.front().id);
      PPtemp.pop();
    }
    /* IO Idle*/
    if(io_idle){
      //If theres job taht can be sent to IO
      if(CPU.empty(false)){
	printf("IO QueProcessor idle");
      }
      else{
	if ( CPU.setJob(false)){
	  printf("New IO process%d", CPU.IO.id);
	  io_idle=false;
	}
	else if (CPU.IO.State=IO_REQUEST){
	  printf("\t%d\t%d", CPU.CPUQueue.size(), CPU.IOQueue.size());
	}
      }
    }
    else{
	CPU.IO--;
      printf("IO job %d: time %d", CPU.IO.id, CPU.IO.timeleft);
	if(CPU.IO.State==IO_DONE){
	  printf("Current IO job done\t");
	  io_idle=true;
	  CPU.Back(false);
	}
    }
    printf("\t\t");

    
    /*CPU Idle #FF0000*/
    if(cpu_idle){
      //If theres job taht can be sent to IO
      if(CPU.empty()){
	printf("CPU QueProcessor idle");
      }
      else{
	if(CPU.setJob()){
	    printf("New CPU process %d", CPU.CPU.id);
	    cpu_idle=false;
	}
      }
    }
    else{
	CPU.CPU--;
      printf("CPU job %d: time %d", CPU.CPU.id, CPU.CPU.timeleft);
	if(CPU.CPU.State==IO_REQUEST){
	  printf("Current CPU job done");
	  cpu_idle=true;
	  CPU.Back();
	}
	else if(CPU.CPU.timerun>=Quant){
	  printf("CPU is premeted");
	  cpu_idle=true;
	  CPU.Premeted();
	}
	else if (CPU.CPU.State=IO_DONE){
	  printf("\tWTF man%d\t%d", CPU.CPUQueue.size(), CPU.IOQueue.size());
	}
    }
    printf("\t\t");
    // Print contents of readyqueue
    //CPU.print();
    

    printf("\n");
    i++;

  }
  
}

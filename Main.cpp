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
  Process ptemp1(atemp1, 5, 1);
  Process ptemp2(atemp2, 7, 2);
  Process ptemp3(atemp3, 1, 3);
  Processor CPU;
  CPU.push(ptemp2);
  CPU.push(ptemp1);
  CPU.push(ptemp3);
  int Quant=15;

  int i=0;
  bool io_idle=true;
  bool cpu_idle=true;

  while(i<50){
    printf("Time:%d\t", i);
    // JObs arrived
    

    printf("CPUQueue:%d IOQueue:%d\t", CPU.size(), CPU.size(false));
    
    // IO Idle
    if(io_idle  || CPU.IO.id==-11){
      if(CPU.empty(false) || CPU.IO.id==-11  ){
	printf("The IO processor is empty\t");
	}
	else{
	  CPU.setJob(false);
	  if(CPU.IO.id!=-11){
	    printf("IO new job process of %d \t", CPU.IO.id);
	    io_idle=false;
	  }
	  else
	    printf("The IO processor is empty\t");
	}
    }
    else{
      --CPU;
      printf("IO ran job  of %d tiem %d\t\t", CPU.IO.id, CPU.IO.timeleft);
	if(CPU.IO.timeleft==0){
	  printf ("IOjob blocked\t");
	  io_idle=true;
	  if(CPU.size(false)>1){
	    CPU.PopBack(false);
	    CPU.setJob (false);
	  }
	  else{
	    printf("IO job finish but no next IO job\t");
	  }
	}
    }

    //CPU I
    if(cpu_idle || CPU.CPU.id==-11 ){
      if(CPU.empty() || CPU.CPU.id == -11){
	  printf("The CPU processor is empty\t");
	}
	else{
	  CPU.setJob();
	  if(CPU.CPU.id != -11){
	  printf("CPU got new job process of %d \t", CPU.CPU.id);
	  cpu_idle=false;
	  }
	  else{
	    printf("The CPU processor is empty\t");
	  }
	}
    }
    else{
      CPU--;
      printf("CPU has job process of %d tiem %d\t", CPU.CPU.id, CPU.CPU.timeleft);
      //Put in staticis here.
      if(Quant <= CPU.CPU.timerun){
	printf ("FUCK THIS PREMETEGINIGN\t");
	CPU.Premeted();
	CPU.setJob();
	cpu_idle=true;
      }
      else{
	if(CPU.CPU.timeleft==0){
	  printf ("This CPUjob is blocked\t");
	  if(CPU.size()>1){
	    CPU.PopBack();
	    CPU.setJob ();
	    cpu_idle=true;
	  }
	  else{
	    printf("CPU job finish but no next CPU job\t");
	  }
	}
      
      }

    }

    // Print contents of readyqueue
    CPU.print();
    

    printf("\n");
    i++;

  }
  
}

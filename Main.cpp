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
  int atemp1[s1]={2,2,2};
  int atemp2[s1]={3,3,3};
  Process ptemp1(atemp1, s1, 2);
  Process ptemp2(atemp2, s1, 3);
  Processor CPU;
  CPU.push(ptemp2);
  CPU.push(ptemp1);
  CPU.push(ptemp2);
  CPU.push(ptemp1);
  int Quant=5;

  int i=0;
  bool io_idle=true;
  bool cpu_idle=true;

  while(i<25){
    // JObs arrived
    printf("Time:%d\t", i);

    printf("CPUQueue:%d IOQueue:%d\t", CPU.size(), CPU.size(false));
    
    // IO Idle
    if(io_idle){
      if(CPU.empty(false)  ){
	printf("The IO processor is empty\t");
	}
	else{
	  CPU.setJob(false);
	  printf("IO new job process of %d \t", CPU.IO.id);
	  io_idle=false;
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
    if(cpu_idle ){
      if(CPU.empty()){
	  printf("The CPU processor is empty\t");
	}
	else{
	  CPU.setJob();
	  printf("CPU got new job process of %d \t", CPU.CPU.id);
	  cpu_idle=false;
	}
    }
    else{
      CPU--;
      printf("CPU has job process of %d tiem %d\t", CPU.CPU.id, CPU.CPU.timeleft);
      //Put in staticis here.
      if(Quant <= CPU.CPU.timerun){
	printf ("FUCK THIS PREMETEGINIGN\t");
	CPU.PopBack();
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

    printf("\n");
    i++;

  }
  
}

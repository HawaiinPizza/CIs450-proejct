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
  while(i<50){
    i++;
    printf("Time:%d\t",i);

    //New jobs come in.

    printf("Size of IQueue:%d and size of CPUqueue%d\t", CPU.IOQueue.size(), CPU.IOQueue.size() );
    //IO_idle state.
    if(io_idle){
      if ( CPU.empty(false) )
	cout << "No jobs coming in for IO\t";
      else{
	CPU.setJob(false);
	io_idle=false;
	printf("IO is now running %d\t", CPU.IO.id);
	io_idle=false;
      }
    }
    else{
      --CPU;

      if(CPU.IO.id==IO_DONE){
	printf("IO of process id has been IO_Done.\t", CPU.IO.id);
	CPU.PopBack(false);
	io_idle=true;
      }
      else{
	printf("IO is running id %d of tiem left %d\t", CPU.IO.id, CPU.IO.timeleft);
      }
    }

    //CPU Idle
    if(cpu_idle){
      if(CPU.CPUQueue.empty()){
	printf("Ready queue is idle\t");
      }
      else{
	CPU.setJob(false);
	cpu_idle=false;
	printf("CPU job of process %d is arriving to be run of time %d left\t", CPU.CPU.id, CPU.CPU.timeleft);
      }
    }
    else{
      if(CPU.CPU.State==IO_REQUEST){
	int temp=CPU.CPU.id;
	CPU.PopBack();
	printf("CPU job is IO_REQUEST from process %d now is %d\t", temp, CPU.CPU.id);
      }
      else{
	CPU--;
	printf("CPU job from process %d is running with %d left\t", CPU.CPU.id, CPU.CPU.timeleft);
      }
    }


    printf("\n");
  }

  //CPU is empty


  /*
  while(!CPU.AllEmpty()){
    CPU--;
    switch(CPU.validJobs()){
    case valid:
      cout << "YEa\n";
      break;
    case cpu:
      cout << "CPU is going get teh fuck outt here\n";
      CPU.PopBack();
      break;
    case io:
      cout << "IO is a muppet\n";
      CPU.PopBack(false);
      break;
    }
  }
  */
  
}

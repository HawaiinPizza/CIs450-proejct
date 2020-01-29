//Header info ignore
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct Event;
struct Process;

//This is the state a job can be in.
enum JobState{ARRIVAL,  PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION };
enum EventTerm{valid, cpu, io};

//THIS holds events that will be used to simulate events
struct Event{
  JobState State=ARRIVAL;
  int timeleft=0;
  int timerunning=0;
  int id;
  bool isCPUjob=true;
  

  //This is the null event. An event that has nothing in it.
  //This is used for testing:: Dont alter value unless willing to hceck for that.
  Event(){
    id=-1;
  }

  Event(int timeToExecute, int process_id, bool CPU){
    timeleft=timeToExecute;
    id=process_id ;
    isCPUjob=CPU;
  }

  void operator--(int){
    timeleft--;
    timerunning++;
    if(timeleft<=0){
      if(isCPUjob){
	State=IO_REQUEST;
      }
      else{
	State=IO_DONE;
      }
      
    }
      
  }
  
};

//This is where a collection of jobs are stored in, as well as the statiics
struct Process{
  int id;
  queue<Event> jobs;
  int waitTime=0;
  int runTime=0;
  int IOWait=0;


  void operator++(int){
	  waitTime++;
	  runTime++;
	  IOWait++;
  }

  //Null process. This process is empty.
  Process(){
    id=-1;
  }

  Process(int* Arr, int size, int ProcessorID){
    for(int i=0; i<size; i++){
      if(i%2==0)
	jobs.push(Event(Arr[i], ProcessorID, true));
      else
	jobs.push(Event(Arr[i], ProcessorID, false));
    }
    id=ProcessorID;
  }


  int size(){
    return jobs.size();
  }

  bool empty(){
    return jobs.empty();
  }

  Event pop(){
    if(empty()){
      //Return null event
      return Event();
    }
    else{
      Event temp=jobs.front();
      jobs.pop();
      return temp;
    }
  }



};


//This holds the current time, as well as the currently running IO/CPU job
struct Processor{

  int id;
  queue<Process> CPUQueue;
  queue<Process> IOQueue;
  int CPUUsage=0;

  //One way of extending to multiple CPU, is to create an array of CPU/IO
  //Than, have a bool array, like CPU_idleArr and IO_idleArr, and those reperesnts processors
  //That are being used.
  Event CPU;
  Event IO;

  //Running process operators
  void operator--(int){
    CPU--;
    CPUUsage++;
  }

  //Running process operators
  void operator--(){
    IO--;
    IOQueue.front()++;
  }

  //If any of the jobs currenlty in the cpu have a process id of -1, that means they're done.
  //enum EventTerm{valid, ECPU, EIO};
  EventTerm validJobs(){
    if(CPU.State == IO_REQUEST && IO.State == IO_DONE)
      {
      if(CPU.State == IO_REQUEST)
	return cpu;
      else
	return io;
      }
	  
    return valid;
  }

  //Queue operators
  void push(Process temp, bool isCPU=true){
    if(isCPU)
	return CPUQueue.push(temp);
    return IOQueue.push(temp);
  }

  int size(bool isCPU=true){
    if(isCPU)
	return CPUQueue.size();
    return IOQueue.size();
     
  }

  bool empty(bool isCPU=true){
    if(isCPU)
	return CPUQueue.empty();
    return IOQueue.empty();
  }

  bool AllEmpty(){
    if (CPUQueue.empty() && IOQueue.empty() )
      return true;
    return false;
  }

  Process front(bool isCPU=true){
    if(isCPU)
      return CPUQueue.front();
    return IOQueue.front();
  }


  void PopBack(bool isCPU=true){
    Process tempProcess=CPUQueue.front();
    if(isCPU){
	Process tempProcess=CPUQueue.front();
	Event JobReturn=tempProcess.pop();
	if(JobReturn.id == -1){
	  printf("This job has termianted, of id of %d.", tempProcess.id);
	}
	else{
	  IOQueue.push(tempProcess);
	  CPUQueue.pop();
	}
    }
    else{
	Process JobReturn=IOQueue.front();
	CPUQueue.push(JobReturn);
	IOQueue.pop();
    }
  }

  void getJob(bool isCPU=true){
  }

  void Premeted(){

  }

  Processor(){
    id=-1;
  }
  
};

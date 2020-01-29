//Header info ignore
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct Event;
struct Process;

//This is the state a job can be in.
enum JobState{ARRIVAL,  PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION };

//THIS holds events that will be used to simulate events
struct Event{
  JobState State=ARRIVAL;
  int timeleft=0;
  int timerunning=0;
  int id;
  bool isCPUjob=true;
  

  Event(){
    id=-1;
  }

  Event(int timeToExecute, int process_id, bool CPU){
    timeleft=timeToExecute;
    id=process_id ;
    isCPUjob=CPU;
  }
  
};

//This is where a collection of jobs are stored in, as well as the statiics
struct Process{
  int id;
  queue<Event> jobs;
  int waitTime=0;
  int runTime=0;
  int IOWait=0;



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
      cout << "YES";
      return Event();
    }
    else{
      cout << "NO";
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

  void push(Process temp, bool isCPU=true){
    if(isCPU)
	return CPUQueue.push(temp);
    return IOQueue.push(temp);
  }

  int size(bool isCPU){
    if(isCPU)
	return CPUQueue.size();
    return IOQueue.size();
     
  }

  bool empty(bool isCPU){
    if(isCPU)
	return CPUQueue.empty();
    return IOQueue.empty();
  }

  Event PopBack(bool isCPU){
    if(isCPU){
	Process temp=CPUQueue.front();
	Event JobReturn=temp.pop();
	if(JobReturn.id == -1)
	  printf("This job has termianted, of id of %d.", temp.id);
	CPUQueue.push(temp);
	CPUQueue.pop();
    }
    Process temp=IOQueue.front();
    IOQueue.push(temp);
    IOQueue.pop();
    return temp.pop();
  }

  Processor(){

  }
  
};

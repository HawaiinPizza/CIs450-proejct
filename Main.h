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
  int timerun=0;
  int id;
  bool isCPU=true;
  

  //This is the null event. An event that has nothing in it.
  //This is used for testing:: Dont alter value unless willing to hceck for that.
  Event(){
    id=-1;
  }

  Event(int timeToExecute, int process_id, bool CPU){
    timeleft=timeToExecute;
    id=process_id ;
    isCPU=CPU;
  }

  void operator--(int){
    if(timeleft>0 && timerun>=0){
	timeleft--;
	timerun++;
    }
    if(timeleft<=0){
      if(isCPU){
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
  int IOTime=0;
  int arrTime;

  void incWait(){
    waitTime++;
  }

  void incRun(){
    runTime++;
  }

  void incIO(){
    IOTime++;
  }


  //Null process. This process is empty.
  Process(){
    id=-1;
  }

  Process(int* Arr, int size, int ProcessorID, int ArrTime){
    arrTime=ArrTime;
    for(int i=0; i<size; i++){
      if(i%2==0){
	jobs.push(Event(Arr[i], ProcessorID, true));
      }
      else{
	jobs.push(Event(Arr[i], ProcessorID, false));
      }
    }
    id=ProcessorID;
  }

  Event front(){
    return jobs.front();
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
      Event Wrong;
      Wrong.id=-11;
      return Wrong;
    }
    else{
      Event temp=jobs.front();
      jobs.pop();
      return temp;
    }
  }

  void push(Event temp){
    jobs.push(temp);
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
  }

  // Sets the current job from the first element in CPU/IOQueue
  bool setJob(bool isCPU=true){
    if(isCPU){
      if(!CPUQueue.front().empty()){
	CPU=CPUQueue.front().pop();
	if(CPU.isCPU == false)
	  printf("This is fuckign weird. CPU is an IO");
	return true;
      }
      else
	return false;
      }
    else{
      if(!IOQueue.front().empty()){
	IO=IOQueue.front().pop();
	if(IO.isCPU == true)
	  printf("This is fuckign weird. CPU is an IO");
	return true;
      }
      else
	return false;
    
    }
  }
  
  void Back(bool isCPU=true){
    if(isCPU){
      if(!CPUQueue.front().empty()){
	IOQueue.push(CPUQueue.front());
	CPUQueue.pop();
      }
      else{
	printf("%d is going to be terminated", CPUQueue.front().id);
	CPUQueue.pop();
      }
    }
    else{
      if(!IOQueue.front().empty()){
	CPUQueue.push(IOQueue.front());
	IOQueue.pop();
      }
    }
  }
  
  void Premeted(){
	CPUQueue.push(CPUQueue.front());
	CPUQueue.pop();
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




  void print(){
    printf("CPUqueue:%d ", CPUQueue.size());
    queue<Process> temp;
    while (!CPUQueue.empty()){
      temp.push(CPUQueue.front());
      cout << CPUQueue.front().size() << "  ";
      CPUQueue.pop();
    }
    CPUQueue=temp;
    printf("IOqueue size %d", CPUQueue.size());
  }
  

  Processor(){
    id=-1;
  }
  
};

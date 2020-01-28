//Header info ignore
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct Event;

//This is the state a job can be in.
enum JobState{ARRIVAL,  PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION };

//This is where a collection of jobs are stored in, as well as the statiics
struct Process{
  const int id;
  queue<Event> jobs;
};

//THIS holds events that will be used to simulate events
struct Event{
  JobState State=ARRIVAL;
  int timeleft=0;
  int timerunning=0;
  Process* parProcess;
  int process_id;
  

  Event(){
  }

  Event(int timeToExecute, Process& ParentProcess){
    timeleft=timeToExecute;
    parProcess=&ParentProcess;
    process_id=parProcess->id;
  }
  
};

//This holds the current time, as well as the currently running IO/CPU job
struct Processor{
  
};

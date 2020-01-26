#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL, PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION};

struct Event{
	int process_id;
	int timeleft;

	Event(){
	}
	Event(int left){
		timeleft=left;
	}
	Event(int left, int proc){
		timeleft=left;
		process_id=proc;
	}

	Event  operator--(int){
		timeleft--;
		if(timeleft>0){
			return Event(timeleft,process_id);
		}
		else{
			return Event(timeleft,process_id);
		}
	}


	
};

struct Process{

	queue<Event> jobs;
	int size;
	int arrive;
	int pos=0;
	JobState type=ARRIVAL;

	Process(int* Times, int Arrival, int Size){
		arrive=Arrival;
		size=Size;
		for(int i=0; i<Size; i++){
			Event temp;
			temp=Times[i];
			temp.process_id=Arrival;
			jobs.push(temp);
		}
	}

	bool empty(){
		return jobs.empty();
	}

	void print(){
		for(int i=0; i<size; i++){
			Event temp=jobs.front();
			cout << temp.timeleft<<endl;
			jobs.pop();
		}
		cout << endl;
	}

	Event pop(){
		Event temp=jobs.front();
		jobs.pop();
		size=jobs.size();
		pos++;
		return temp;
	}

};


struct Pointer{
	int PointSize;

	//This is to keep track of the next job that will arrive
	int NextArrive=0;
	int *JobTime;

	//This is to keep track of the next job that will 
	int NextJob=0;
	Process *ProcessList;


	int JobArrive(int time){
		for(int i=0; i<PointSize;i++){
			if(JobTime[NextArrive]==time){
				NextJob=NextArrive;
				NextArrive++;
			}
		}
		return NextJob;
	}

	void SwapProcess(){
	}

	Event GetEvent(){
		Event temp=ProcessList[NextJob].pop();

		int i=0;
		if(ProcessList[NextJob].empty()){
			cout << "Job\n";
			NextJob--;
		}
		if(i>=PointSize){
			return ProcessList[NextJob].pop();
		}
		else{
			cout << "YES";
			cout << "We're done \n";
			return Event(-1);
		}
	}

	Pointer(int* ArriveOrder, Process* ListProcess, int size){
		JobTime=ArriveOrder;
		ProcessList=ListProcess;
		PointSize=size;


	}

};


int main(){
	/* the following pseudocode assumes C++ pointer syntax */
	bool io_idle = true; 
	bool cpu_idle = true;
	int sim_time = 0;
	/*
	   2 5 8 7	 4
	   4
	   8 2 10 2 	7 5 6
	 */
	int Arrival[3]={3,5,6};
	int Pos=0;
	int P3T[]={2,5,8,7,4};
	int P5T[]={4};
	int P6T[]={8,2,10,2,7,5,6};
	queue<int> wow;
	Process P3(P3T, 3, 5);
	Process P5(P5T, 5, 1);
	Process P6(P6T, 6, 7);
	Process PList[]={P3,P5,P6}; 
	sim_time=Arrival[0];
	Event CurrJob;
	int ProcessSize=3;
	Pointer Test(Arrival, PList, ProcessSize);
	while(CurrJob.timeleft!=-1){
		cout << "WHAT\n";
		CurrJob=Test.GetEvent();
	}




	// Important variables
	// ProcessSize: Number of processess
	// Arrival array: The time in which an array will arrive
	// Pos: a pointer to the array, to show the NEXT process it will be running
	// io_idle/cpu_idle: see if the cpu is not idle
	// Order is the next procses to arrive
	//Event *ev = select and remove the earliest event from the event list;



//	   int pid = ev->process_id;
//	   while (sim_time < ev->time)
//	      {sim_time = sim_time + 1; /* advance the simulation time */
//		/* output “no event” to log */
//	   else
//	     {  
//	      switch (ev->type)
//		{
//		   case ARRIVAL:
//		       /* create a new (simulated) process and place it in the Ready Queue */
//		      ...
//		       /* output “arrival event” to log */ 
//		      break;
//		  case PREEMPTION:
//		      /* put the current process in the Ready Queue */
//		      cpu_idle = TRUE;
//		      ...
//		  /* output “preemtion event” to log */
//		      break;
//		  case IO_REQUEST:
//		       /* free CPU and move the current process into the I/O Queue */
//		      cpu_idle = TRUE;
//		      ...
//		  /* output “I/O request event” to log */ 
//		      break;
//		  case IO_DONE:
//		      /* free I/O device and put the process in the Ready Queue */
//		      io_idle = TRUE;
//		      ...
//		  /* output “IO done event” to log */
//		      break;
//		  case TERMINATION:
//		      /* free up the CPU, update statistics of the entire simulation */
//		      cpu_idle = TRUE;
//		      ...
//		  /* output “termination event” to log */
//		      break;
//	       }
//	       if (cpu_idle and there are jobs to dispatch) 
//		{
//		   cpu_idle = FALSE;
//		   dispatch_a_process();  /* remove the first process from the Ready Queue */
//		/* output “job dispatch event” to log */	
//		 }
//	       if (io_idle and there are jobs waiting to perform I/O)
//	     {
//		io_idle = FALSE;
//		do_IO_operation (...); /* remove the first process from the I/O Queue */
//		/* output “I/O operation event” to log */ 	
//	     } 
//	  } /* end switch */
//	}   /* end if         */

}

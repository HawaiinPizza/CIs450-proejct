#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL, PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION};


struct Event{
	int time;
	int process_id;
	bool isCPU;
	JobState State=ARRIVAL;

	void operator--(int){
		time--;
		if(time<1){
			if(isCPU){
				cout << "YES";
				State=IO_REQUEST;
			}
			else
			{
				cout << "YES";
				State=IO_DONE;
			}
		}
	}

	void operator=(const Event& temp){
		time=temp.time;
		process_id=temp.process_id;
		isCPU=temp.isCPU;
	}

	Event(int Arr,  int Process, bool CPU){
		time=Arr;
		process_id=Process;
		isCPU=CPU;
		}
	};

struct point{
	int Pos=0;
	int* Order;
	int Qunatom;
	int size;

	int WhenNext(){
		if(Pos<size)
			return Order[Pos];	
		else
			return -1;
	}


	bool NextNow(){
		if(Pos<size ){
			Pos++;
			return true;
		}
		return false;
	}

	point(int* Temp, int Size){
		Order=Temp;
		size=Size;
	}
};

struct Process{
	queue<Event> Jobs;
	Process(int *Arr, int size, int Process){
		for(int i=size-1; i>-1; i--){

			if(i%2==0)
				Jobs.push(Event(Arr[i], Process, true));
			else
				Jobs.push(Event(Arr[i], Process, false));

		}
	}

	Event pop(){
		Event temp=Jobs.front();
		Jobs.pop();
		return temp;
	}

	bool empty(){
		return Jobs.empty();
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

	queue<Process> ReadyQueue;

	int P1[]={2,5,8,7,4};
	int P2[]={4};
	int P3[]={8,2,10,2,7,5,6};
	Process Pp1(P1, 5, 1);
	Process Pp2(P2, 5, 2);
	Process Pp3(P3, (4+3), 3);
	queue<Process> All;
	All.push(Pp1);
	All.push(Pp2);
	All.push(Pp3);
	int ArrivalTime[]={3,5,6};
	int i=0;
	point Pointer(ArrivalTime, 3);
	Event CurrJob(-1,-1,false);
	
	//while(!ReadyQueue.empty() && !All.empty())
	while(i<50){
		cout << i << '\t';
		if(Pointer.WhenNext()==i){
			ReadyQueue.push(All.front());
			cout << "New job: " << ReadyQueue.size() << '\t';
			All.pop();
			Pointer.NextNow();
		}

		if(!ReadyQueue.empty() && !ReadyQueue.front().empty() )
		{
			printf("Runtime of %d, of process id %d\t", CurrJob.time, CurrJob.process_id);
			CurrJob--;
			if(CurrJob.State==IO_REQUEST ||  CurrJob.State==IO_DONE){
				CurrJob=ReadyQueue.front().pop();
			}
		}
		else if(!ReadyQueue.empty() && ReadyQueue.front().empty()) {
			printf("Queue is empty %d:\t%d", i, ReadyQueue.size());
		}
		else{
			cout << "New job coming in\t";
			//CurrJob=ReadyQueue.front().pop();
		}


		cout << endl;

		i++;
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

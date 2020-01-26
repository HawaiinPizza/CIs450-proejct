#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL, PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION};


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

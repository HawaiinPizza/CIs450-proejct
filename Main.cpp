#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL,  PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION };


struct Event{
	int time;
	int process_id;
	bool isCPU;
	JobState State;

	void operator--(int){
		time--;
		if(time==0){
			if(isCPU){
				State=IO_REQUEST;
			}
			else
			{
				State=IO_DONE;
			}
		}
	}

	void operator=(const Event& temp){
		time=temp.time;
		process_id=temp.process_id;
		isCPU=temp.isCPU;
		State=temp.State;
	}

	Event(int Arr,  int Process, bool CPU){
		time=Arr;
		process_id=Process;
		isCPU=CPU;
		if(isCPU==1)
			State=ARRIVAL;
		else
			State=ARRIVAL;
		}
	Event(){
		time=-1;
		process_id=-1;
		isCPU=false;
		State=ARRIVAL;
		}
	};

struct point{
	int Pos=0;
	int* Order;
	int Qunatom;
	int size;
	Event CPU;
	Event IO;

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

	void ChangeJob(Event newJob){
		if(newJob.isCPU)
			CPU=newJob;
		else
			IO=newJob;
	}

	bool IsEmpty(){
		if(CPU.process_id!=-1 || IO.process_id!=-1)
			return false;
		return true;
	}

	void operator--(int){
		CPU--;
		IO--;
	}
};

struct Process{
	queue<Event> Jobs;
	Process(int *Arr, int size, int Process){
		for(int i=0; i<size; i++){

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

	int size(){
		return Jobs.size();
	}

	Event front(){
		return Jobs.front();
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
	queue<Process> IO;

	int P1[]={2,5,8,7,4};
	int P2[]={4};
	int P3[]={8,2,10,2,7,5,6};
	Process Pp1(P1, 5, 1);
	Process Pp2(P2, 1, 2);
	Process Pp3(P3, 7, 3);
	queue<Process> All;
	All.push(Pp1);
	All.push(Pp2);
	All.push(Pp3);
	int ArrivalTime[]={3,5,6};
	int i=0;
	point Pointer(ArrivalTime, 3);
	while(i<100){

		cout << endl;

		i++;
	}
}

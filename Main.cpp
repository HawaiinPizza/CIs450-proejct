#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL, PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION };


struct Event{
	int time;
	int process_id;
	bool isCPU;
	JobState State=ARRIVAL;

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
		}
	Event(){
		time=-1;
		process_id=-1;
		isCPU=false;
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
		if(CPU.process_id!=-1 && IO.process_id!=-1)
			return false;
		return true;
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
	Event CurrJob(-1,-1,false);
	
	//while(!ReadyQueue.empty() && !All.empty())
	int Pos=0;
	while(i<100){
		cout << i << '\t';
		if(Pointer.WhenNext()==i){
			ReadyQueue.push(All.front());
			cout << "New job: " << ReadyQueue.size() << '\t';
			All.pop();
			Pointer.NextNow();
		}

		
		// CPU Handling
		if(Pointer.CPU.process_id!=-1){
				printf(" Runtime:%d,   id%d,   cpu%d    size%d\t",  Pointer.CPU.time, Pointer.CPU.process_id, Pointer.CPU.isCPU, ReadyQueue.front().Jobs.size());

				Pointer.CPU--;
				switch(Pointer.CPU.State){
					case ARRIVAL:
						cout << "ARRIVE\t";
						break;
					case PREEMPTION:
						cout << "PREEMPTION\t";
						break;
						//Modify as to push teh next io job to IO queue. Than, let another process run
						//So if P1 is in CPU, than have P1 be in I/O, P2 in CPU, and P1 is pushed to queue.
					case IO_REQUEST:
						cout << "IO_REQUEST\t";
						if(!ReadyQueue.front().empty() ){
							Pointer.CPU=ReadyQueue.front().pop();
							break;
						}
						else{
							cout << "YEAAA!";
							Pointer.CPU.State=TERMINATION;
							break;
						}
						//Modify as to push teh next io job to CPU queue. Than, let another process run
						//So if P1 is in I/O, than have P1 be in CPU, P2 in IO, and P1 is pushed to queue.
					case IO_DONE:
						cout << "IO_DONE\t";
						if(!ReadyQueue.front().empty()){
							Pointer.CPU=ReadyQueue.front().pop();
							break;
						}
						else{
							Pointer.CPU.State=TERMINATION;
							break;
						}
					case TERMINATION :
						cout << "TERMINATION\t";
						if( ReadyQueue.size()==1){
							cout << "FINISH YES\t";
							ReadyQueue.pop();
							Pointer.CPU.process_id=-1;
						}
						else{
							cout << ReadyQueue.size() << " Before size\t";
							ReadyQueue.pop();
							cout << ReadyQueue.size() << " After size\t";
							Pointer.CPU=ReadyQueue.front().pop();
						}

						break;
				}
		}
		else if (CurrJob.process_id==-1){
			if(!ReadyQueue.empty() && !ReadyQueue.front().empty() ){
				Pointer.CPU=ReadyQueue.front().pop();
				cout << "Queue job: " << ReadyQueue.size() << '\t';
			}
			else
				printf("Queue is empty ");
				
		}

		/*
		*/


		cout << endl;

		i++;
	}
}

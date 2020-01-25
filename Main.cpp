#include<stack>
#include<iostream>
#include<algorithm>
using namespace std;

enum JobState{ARRIVAL, PREEMPTION, IO_REQUEST, IO_DONE, TERMINATION};
struct Job{
	int time;
	bool CPUType;
	Job* Next;
	JobState State=ARRIVAL;

	void Dec(int delta){
		time-=delta;
	}
	Job(int Time, bool CPU){
		time=Time;
		CPUType=CPU;
	}
	Job(){
		time=NULL;
		CPUType=NULL;
	}
} ;


struct Process{
	int size=0;
	Job * Head=new Job;
	int Arrival=0;
	void Set(int* List, int Size, int ArrivalTime){
		Arrival=ArrivalTime;
		Job * Curr=new Job;
		Curr=Head;
		for(int i=0; i<=Size; i++){
			Curr->time=List[i];
			if(i%2==0)
				Curr->CPUType=true;
			else
				Curr->CPUType=false;

			Job * Temp=new Job;
			Curr->Next=Temp;
			Curr=Temp;
		}
		Curr->Next=NULL;
		size=Size;
	}
	Process(){
	}
	Process(int* List, int Size, int Arrival){
		Set(List,  Size, Arrival);
	}

	void Print(){
		Job * Curr=Head;
		for(int i=0; i<=size; i++){
			printf("Time:%d\tType:%d\n", Curr->time, Curr->CPUType);
			Curr=Curr->Next;
		}
	}

	void PushRQueue(Job Temp){

	}

	void PushRQueue(Job* Temp, int Size){

	}

	void PushIQueue(Job Temp){

	}
	
};
class ReadyQueue{
	public:
		// Given the arguemnts of array of eventlist, time quantom, output log/stdout 
		ReadyQueue(Process* Arr, int quantom, ostream& outlog, ostream& output, int ProcessSize){
			ProcessList=Arr;
			OutLog=&outlog;
			OutStd=&output;
			Size=ProcessSize;
			Order=new int[ProcessSize];
			GetOrder();
		}

		ReadyQueue(Process* Arr, int quantom, int ProcessSize){
			ProcessList=Arr;
			Size=ProcessSize;
			Order=new int[ProcessSize];
			GetOrder();
		}

		void GetOrder(){
			for(int i=0; i<Size; i++){
				Order[i]=ProcessList[i].Arrival;
			}
			sort(Order, Order+Size);
			for(int i=0; i<Size; i++){
				if(i%2==0){
				}
				else
				{
					StackIO.push(ProcessList[i].Head);
				}

			}
		}

		Process *ProcessList=new Process();
		ostream * OutLog;
		ostream * OutStd;
		Job CpuProcess;
		Job IOProcess;
		int Size;
		stack <Job*> StackCPU;
		stack <Job*> StackIO;
		int *Order;


};
int main(){
	int Job1[]={2,5,8,7,4};
	Process Test1(Job1,5, 3);
	int Job2[]={ 4};
	Process Test2(Job2,1, 5);
	int Job3[]={ 8,2,10,2,7,5,6};
	Process Test3(Job2,4, 6);

	Process Temp[]={Test1,Test2, Test3};
	Process * What=Temp;

	ReadyQueue Town(What, 3, 3);

	//Time to actually start
	int time=Town.Order[0];
	Job IO;
	Job CPU;
	IO.CPUType=false;
	CPU.CPUType=true;
	int Next=Town.Order[1];
	int Pos=1;

	while(CPU.time>0){
		CPU.time--;
		time++;
	}

	int OverBoard=0;
	while(Pos<Town.Size){
		time++;
		OverBoard++;
		CPU.time--;
		if(Town.Order[Pos]==time){
			// Figure out how to sort this
			Town.StackCPU.push(Town.ProcessList[Pos].Head);
			Pos++;
		}


		bool ChangeJob=false;
		if(CPU.time<0 ){
			if(CPU.Next==NULL){
				ChangeJob=true;
				CPU.State=IO_REQUEST;
			}
			else if(OverBoard>Town.quantom){
				ChangeJob=true;
				CPU.State=PREEMPTION;
				
			}

		}
		else if(ChangeJob){
			CPU=*Town.StackCPU.top();
			Town.StackCPU.pop();

		}
		else{
		}
	}




	



}


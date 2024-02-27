#include<bits/stdc++.h>
using namespace std;

#define numProcesses 5

struct Process{
    int process_id;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int arrival_time;
    int priority;
};
bool comparator(Process a,Process b){
    return a.priority>b.priority;
};

int main(){
    freopen("input.txt", "r", stdin);
    vector<Process> process(numProcesses);
    vector<int> arrival_time(numProcesses);
    arrival_time[0] =0;//hard coded
    int value,wait_sum=0,turn_sum=0;

    for(int i=0;i<numProcesses;i++){
        cin>>value;
        process[i].burst_time=value;
        cin>>value;
        process[i].priority=value;
        process[i].process_id=i+1;
    }

    sort(process.begin(),process.end(),comparator);
    process[0].turnaround_time=process[0].burst_time;
    process[0].waiting_time=0;
    for(int i=1;i<=numProcesses;i++){
        process[i].turnaround_time=process[i-1].turnaround_time+process[i].burst_time;
        process[i].waiting_time=process[i].turnaround_time-process[i].burst_time;
    }
    cout<<"Gant chart:"<<endl;
    cout<<"|";
    for(int i=0;i<numProcesses;i++){
        cout<<"---P"<<process[i].process_id<<"---|";
    }
    cout<<endl;
    printf("%-9d",0);
    for(auto p:process){
        printf("%-9d",(p.turnaround_time));
    }
    cout<<endl<<endl;

     printf("%s\t%s\t\t%s\n","Process ID","Turnaround Time","Waiting Time");
    for(auto p:process){
        printf("P%d %20d %23d\n",p.process_id,p.turnaround_time,p.waiting_time);
        wait_sum+=p.waiting_time;
        turn_sum+=p.turnaround_time;
    }
    cout<<"Average turnaround time: "<<(double)turn_sum/numProcesses<<endl;
    cout<<"Average waiting time: "<<(double)wait_sum/numProcesses<<endl;



    
}
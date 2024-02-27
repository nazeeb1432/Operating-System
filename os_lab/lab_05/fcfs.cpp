#include<bits/stdc++.h>
using namespace std;

#define n 5

int turnTime[n],cmpTime[n],waiting_time[n];

int calc_turnaround_time(int completion_time,int arrival_time){
    return completion_time-arrival_time;
}

double calc_avg_turnaround_time(int *arr){
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum/n;
}

double calc_avg_waiting_time(int *arr){
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum/n;
}

int main(){
    
    map<string,int> mp;
    int burst_time[n];
    freopen("fcfs.txt", "r", stdin);
    // cout<<"Enter burst time of the processes: ";
    for(int i=0;i<n;i++){
        cin>>burst_time[i];
    }

    for(int i=1;i<=n;i++){
        mp['P'+to_string(i)]=burst_time[i-1];
    }

    for(auto u:mp){
        cout<<u.first<<" "<<u.second<<endl;
    }

    // |---P1---|---P2---|---P3---|---P4---|---P5---|
    // 0        2        3        11      15       20

    cout<<"Gantt chart:"<<endl;
    cout<<"|";
    for(auto u:mp){
        cout<<"---"<<u.first<<"---|";
    }
    cout<<endl;
    cout<<"0";

    int prev=0;
    for(auto u:mp){
        prev+=u.second;
        // cout<<"        "<<prev;
        printf("%9d",prev);
    }
    cout<<endl;

   // process  waiting time  turnaround time
   // p1       4             9
   // p2       3             7

   cout<<"Process "<<"Waiting time "<<"turnaround time"<<endl;
   prev=0;
   int i=0;
   for(auto u:mp){
    prev+=u.second;
    cmpTime[i]=prev;
    i++;
   }

   for(int j=0;j<n;j++){
    turnTime[j]=calc_turnaround_time(cmpTime[j],0);
   }

   int k=0;
   for(auto u:mp){
    waiting_time[k]=turnTime[k]-u.second;
    k++;
   }
   k=0;

   for(auto u:mp){
    cout<<u.first;
    printf("%12d%12d\n",waiting_time[k],turnTime[k]);
    k++;
   }
   




}
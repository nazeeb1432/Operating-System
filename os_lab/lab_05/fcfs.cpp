#include<bits/stdc++.h>
using namespace std;

#define n 5

int turnTime[n],cmpTime[n],waiting_time[n];

int calc_turnaround_time(int completion_time,int arrival_time){
    return completion_time-arrival_time;
}

// double calc_avg_turnaround_time(int *arr){
//     double sum=0;
//     for(int i=0;i<n;i++){
//         sum+=arr[i];
//     }
//     return sum/n;
// }

// double calc_avg_waiting_time(int *arr){
//     double sum=0;
//     for(int i=0;i<n;i++){
//         sum+=arr[i];
//     }
//     return sum/n;
// }

int main(){

    map<string,int> mp;
    int burst_time[n],turn_sum=0,wait_sum=0,arrival_arr[n];
    freopen("fcfs.txt", "r", stdin);
    // cout<<"Enter burst time of the processes: ";
    for(int i=0;i<n;i++){
        cin>>burst_time[i];
    }
    for(int i=0;i<n;i++){
        cin>>arrival_arr[i];
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
    /*
        ith a_t > i-1th c_t --> ct[i] = at[i] + bt[i]
        else ct[i] = ct[i-1] + bt[i];
    */
     int prev=0;
    // int i =0;
    // for(auto u:mp){
    //     prev+=u.second;
    //     cmpTime[i++] = prev;
    //     // cout<<"        "<<prev;
    //     printf("%9d",prev);
    // }
    arrival_arr[0]=0;
    cmpTime[0]=burst_time[0];
    printf("%9d",cmpTime[0]);
    for(int i=1;i<n;i++){
        if(arrival_arr[i]>cmpTime[i-1]) cmpTime[i]=arrival_arr[i]+burst_time[i];
        else cmpTime[i]=cmpTime[i-1]+burst_time[i];
         //cout<<"        "<<cmpTime[i];
        printf("%9d",cmpTime[i]);
    }
    cout<<endl;

   // process  waiting time  turnaround time
   // p1       4             9
   // p2       3             7

   cout<<"Process "<<"Waiting time "<<"turnaround time"<<endl;


   for(int j=0;j<n;j++){
    // turnTime[j]=calc_turnaround_time(cmpTime[j],arrival_arr[j]);
    // cout << cmpTime[j] << " " << arrival_arr[j] << " " << endl;
    turnTime[j]=cmpTime[j]-arrival_arr[j];
    turn_sum+=turnTime[j];
   }

   int k=0;
   for(auto u:mp){
    // cout << turnTime[k] << " " << u.second << endl;
    waiting_time[k]=turnTime[k]-u.second;
    wait_sum+=waiting_time[k];
    k++;
   }
   k=0;

   for(auto u:mp){
    cout<<u.first;
    printf("%12d%12d\n",waiting_time[k],turnTime[k]);
    k++;
   }
   cout<<endl;
   cout<<"Average turnaround time: "<<(double)turn_sum/n<<endl;
   cout<<"Average waiting time: "<<(double)wait_sum/n<<endl;
   




}
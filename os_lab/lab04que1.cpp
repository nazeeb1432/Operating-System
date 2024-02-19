#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,sumOdd=0,sumEven=0;
    cout<<"Enter the value of n:";
    cin>>n;

    int pid;

    switch(pid=fork()){
        
        case 0: 
               
                for(int i=1;i<=n;i++){
                    if((i%2)!=0)sumOdd+=i;
                }
                printf("I am the child process: %d, and my calculation(odd) is:%d\n",getpid(),sumOdd);
                break;
        default: 
                
                for(int i=1;i<=n;i++){
                    if(i%2==0) sumEven+=i;
                }
                printf("I am the parent process:%d, my child process is: %d, and my calculation(even)is: %d\n",getpid(),pid,sumEven);
                break;

        case -1:
                perror("fork");
                exit(1);
                break;
    }

    exit(0);
}
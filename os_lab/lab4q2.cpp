#include<bits/stdc++.h>
using namespace std;
#include<sys/wait.h>

int main(){
    int r1,c1,r2,c2,pid;
    freopen("lab4q2_input.txt", "r", stdin);
    cin>>r1>>c1;
    cin>>r2>>c2;
    int mat1[r1][c1],mat2[r2][c2],res[r1][c2];

    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            cin>>mat1[i][j];
        }
    }
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            cin>>mat2[i][j];
        }
    }

    for(int i=0;i<r1;i++){
        pid=fork();
        if(pid==0){
            for(int j=0;j<c2;j++){
                res[i][j]=0;
                for(int k=0;k<r1;k++){
                    res[i][j]+=mat1[i][k]*mat2[k][j];
                }
            }
            for(int j=0;j<c2;j++) cout<<res[i][j]<<" ";
            cout<<endl;

            exit(0);
        }
        wait(NULL);
       
    }

    return 0;


}
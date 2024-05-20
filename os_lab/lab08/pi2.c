#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX_VALUE 1
#define MIN_VALUE -1
#define thread_number 5


int n;
float circle_pts=0;
// int arg[2];


int inCircle(float x,float y){
    float dst=sqrt(pow(x,2) + pow(y,2));
    if(dst>1) return 0;
    else return 1;
}

float generate_random(float min,float max){
    
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * (max - min); 
}

void *calcPi(void *param){
    int n1=*(int *)param;
    // printf("%d\n",n1);

    srand(time(NULL));

    for(int i=0;i<n1;i++){
        float x=generate_random(MIN_VALUE,MAX_VALUE);
        float y=generate_random(MIN_VALUE,MAX_VALUE);

        if(inCircle(x,y)){
            circle_pts++;
        }
    }

    pthread_exit(NULL);
}

int main(int argc,char *argv[]){

    pthread_t tid[5];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    //n=2000;
    printf("Enter number of points:");
    scanf("%d",&n);
    int arg=n/thread_number;
    
    for(int i=0;i<5;i++){
        pthread_create(&tid[i],&attr,calcPi,&arg);
    }

    for(int i=0;i<5;i++){
        pthread_join(tid[i],NULL);
    }

    float ans=(4*circle_pts)/n;
    printf("%f\n", ans);
    

    return 0;
}






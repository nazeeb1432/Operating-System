#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX_VALUE 1
#define MIN_VALUE -1


float n;
float circle_pts=0;


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
    n=atoi(param);

    srand(time(NULL));

    for(int i=0;i<n;i++){
        float x=generate_random(MIN_VALUE,MAX_VALUE);
        float y=generate_random(MIN_VALUE,MAX_VALUE);

        if(inCircle(x,y)){
            circle_pts++;
        }
    }

    pthread_exit(NULL);
}

int main(int argc,char *argv[]){

    pthread_t tid;
    pthread_create(&tid, NULL,calcPi,argv[1]);
    pthread_join(tid,NULL);

    float ans=(4*circle_pts)/n;
    printf("%f\n", ans);
    

    return 0;
}






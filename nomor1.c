#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int flag=0;
int store[100];


void *factorial(){
	int fact = 1;
	int i;
	pthread_t id = pthread_self();
	for(i=1; i<=store[flag]; i++){
		fact *= i;
	}
	printf("%d! = %d\n", store[flag],fact);
}

int main(int argc,char* argv[])
{
    int x=argc-1;
    pthread_t tid[argc];
    //simpan argcv di dalam array store
    int i, j;
    for (i=0; i<x; i++){
    	store[i]= atol(argv[i+1]);
    }

    //sort dilakukan dengan bubble sort
    int temp;
    for (i=0; i<x-1; i++){           
       for (j=0; j<x-i-1; j++){
       		if (store[j] > store[j+1]){
       			temp = store[j];
       			store[j] = store[j+1];
       			store[j+1] = temp;
       		}	     
       }              
    }

    // for (i=0; i<x;i++){
    //     printf("%d\n",store[i]);
    // }

    //eksekusi faktorial di setiap threadnya
    while(flag < x){
    	int buat=pthread_create(&tid[flag], NULL, factorial, NULL);
    	if(buat==0){
    		//printf("test\n");
    	}
    	else
    	{
    		fprintf(stderr,"Error: %d", buat);
    	}
    	pthread_join(tid[flag],NULL);
    	flag++;
    }

    return 0;
}

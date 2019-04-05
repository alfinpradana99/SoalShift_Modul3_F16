#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

pthread_t tid1, tid2, tid3;
int WakeUp_Status = 0;
int Spirit_Status = 100;
int counter1, counter2;
int flag;
int asleep, isleep;

void* iraj(void *arg)
{
    while(1) {
        while (flag != 2) {}
        if(counter2==3)
        {
                puts("Iraj Ayo Tidur disabled for 10s");
                counter2=0;
                flag=0;
                isleep = 1;
                sleep(10);
                isleep = 0;
                continue;
        } else 
        {
                Spirit_Status = Spirit_Status - 20;
                printf("Iraj Ayo Tidur!\n");
                counter1++;
                if (counter1 == 3 && asleep == 0) {
                        flag = 3;
                        continue;
                }
        }
        flag=0;
    }
    return NULL;
}

void* agmal(void *arg)
{
    while(1) {
        while (flag != 3) {}
        if(counter1==3) {
//              puts("masuk pak eko");
                puts("Agmal Ayo Bangun disabled for 10s");
                counter1=0;
                flag = 0;
                asleep = 1;
                sleep(10);
                asleep = 0;
                continue;
        } else
        {
                WakeUp_Status = WakeUp_Status + 15;
                printf("Agmal Ayo Bangun!\n");
                counter2=counter2+1;
//                printf("%d", counter2);
                if (counter2 == 3 && isleep == 0) {
                        flag = 2;
                        continue;
                }
        }
        flag=0;
    }
    return NULL;
}

void* status(void *arg)
{
    while(1) {
        while(flag!=1) {}
        printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
        printf("Iraj Spirit_Status = %d\n", Spirit_Status);
        flag=0;
    }
    return NULL;
}


int main()
{
    counter1=0;
    counter2=0;
    asleep = isleep = 0;
    pthread_create(&(tid1), NULL, status, NULL);
    pthread_create(&(tid2), NULL, agmal, NULL);
    pthread_create(&(tid3), NULL, iraj, NULL);
    while(WakeUp_Status < 100 && Spirit_Status > 0)
    {
       while (flag != 0) {}
//      printf("%d %d\n", counter1, counter2);
//       int counter=0;
       if (WakeUp_Status >= 100 || Spirit_Status <= 0) break;
       int input;
       printf("\nSilahkan pilih :\n");
       printf("1. All Status\n");
       printf("2. Iraj Ayo Tidur!\n");
       printf("3. Agmal Ayo Bangun!\n\n");
       scanf("%d", &input);
   
       if(input==1) {
            flag=input;
//          pthread_create(&(tid1), NULL, status, NULL);
//          pthread_join(tid1, NULL);
       }
       else if(input==2) {
            if (!isleep) flag=input;
//          pthread_create(&(tid2), NULL, agmal, NULL);
//          pthread_join(tid2, NULL);
       }
       else if(input==3) {
            if (!asleep) flag=input;
//          pthread_create(&(tid3), NULL, iraj, NULL);
//          pthread_join(tid3, NULL);
       }
    }
    if(WakeUp_Status>=100) printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
    else printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
    
}

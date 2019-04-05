#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <unistd.h>
#define PORT 8080

int *stok;

void *jual(void *arg){

    int *sock_client;
    sock_client = (int *)arg;
    char c_response[100];
    memset(c_response,0,sizeof(c_response));
    while(recv(*sock_client, &c_response, sizeof(c_response), 0)){ 

        if(strcmp(c_response,"jual") == 0){

            *stok=*stok+1;
            char pesan[100] = "transaksi berhasil";
            send(*sock_client, pesan, sizeof(pesan), 0);

        }else{

            char pesan[100] = "Error : Bukan perintah yang tepat.";
            send(*sock_client, pesan, sizeof(pesan), 0);

        }

        printf("client telah mengirim data : %s\n",c_response);
        memset(c_response,0,sizeof(c_response));
    }
}

void *lihatStok(void *arg){

    while(1){
        sleep(5);
        printf("Banyak stok : %d\n",*stok);
    }

}

int main(int argc, char const *argv[]) {
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    stok = shmat(shmid, NULL, 0);

    *stok = 10;

    pthread_t tid1, tid2;

    int sock_serv, sock_client, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    sock_serv = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_serv == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sock_serv, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    pthread_create(&tid2 ,NULL, lihatStok, NULL);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(sock_serv, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sock_serv, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((sock_client = accept(sock_serv, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    char pesan[100] = "Anda telah terhubung ke server!\n";
    send(sock_client, pesan, sizeof(pesan),0);

    pthread_create(&tid1, NULL, jual, (void *)&sock_client);

    pthread_join(tid1,NULL);

    shmdt(stok);
    shmctl(shmid, IPC_RMID, NULL);

    exit(1);
    return 0;
}

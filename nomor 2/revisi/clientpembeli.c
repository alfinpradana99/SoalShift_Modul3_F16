#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    char s_response[100];
    recv(sock, &s_response, sizeof(s_response), 0);
    
    printf("server telah mengirim data : %s\n",s_response);
    memset(s_response,0,sizeof(s_response));

    char pesan[100];
    scanf("%s", pesan);

    while(send(sock, pesan, sizeof(pesan), 0)){
        memset(pesan, 0, sizeof(pesan));

        if(recv(sock,&s_response,sizeof(s_response),0) ){ 
            printf("server telah mengirim data : %s\n",s_response); 
        }
        scanf("%s", pesan);
        memset(s_response,0,sizeof(s_response));
           
    }

    close(sock);
    return 0;
}

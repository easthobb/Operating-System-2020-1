#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#define PORT 10829

int main(){

int s_socket_fd; 
int c_socket_fd;
int fd_array[10][2]={{0,0}}; // [10]각 클라이언트 별로 생성되는 소켓 디스크립터 변수를 저장, [2]:메시지 시퀀스 확인용
struct sockaddr_in server_address, client_address;
socklen_t client_address_size;


/*클라이언트의 접속을 기다리는 서버소켓 객체 생성*/ 
s_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
printf("Server Socket Create!!!\n");

/*서버의 IP 와 PORT 를 저장할 server_address 객체를 0으로 초기화 시킴*/ 
memset(&server_address, 0, sizeof(server_address));

/*server_address 에 서버의 주소 정보 대입*/ 
server_address.sin_family=AF_INET; 
server_address.sin_addr.s_addr=htonl(INADDR_ANY);
server_address.sin_port=htons(PORT);
bind(s_socket_fd, (struct sockaddr*) &server_address, sizeof(server_address));


/*클라이언트의 접속을 기다리는 대기 모드로 전환 - 본 문제에서는 10개의 백로그를 갖습니다.*/ 
listen(s_socket_fd, 10);
printf("Wait Client...\n");

while(1){
client_address_size = sizeof(client_address);
c_socket_fd = accept(s_socket_fd, (struct sockaddr*)&client_address,&client_address_size);// 연결 수락

if(c_socket_fd < 0) //소켓 디스크립터 오류시
{
    printf("Server: accept failed.\n");
    exit(0);
}
else{ // 정상적으로 소켓 디스크립터가 들어올 경우
    printf("where?");
    int flag = 0;// fd_array를 스택 처럼 작동시키기 위해, 최 상위 가르킴
    for(int i = 0; i<10 ; i++){//백로그 갯수만큼 공간 생성 및 순회 

        if(fd_array[i][0]==c_socket_fd)//이미 받았던 fd라면
        {   
            fd_array[i][1]++;
            char fromClient[100]; // Client로 부터받은 메시지 저장 문자열 배열
            char * toClient = malloc(sizeof(char)*100);// Client로 보낼 메시지 배열
            char temp[] ="Hello, Client, this is my reply for your message No.";
            strcpy(toClient,temp);
            strcat(toClient,(char*)fd_array[i][1]);
            read(c_socket_fd, fromClient ,sizeof(fromClient));
            printf("From Client Message: %s\n",fromClient);
            printf("Now sending Message To Client\n");
            write(c_socket_fd, toClient, sizeof(toClient));
            free(toClient);
            break;
        }
        else if(i==9)//처음 받는 fd 일 경우 스택에 저장
        {
            fd_array[flag][0]=c_socket_fd;//flag에 해당하는 위치에 fd 저장
            fd_array[flag][1]=0;
            char fromClient[100]; // Client로 부터받은 메시지 저장 문자열 배열
            char * toClient = malloc(sizeof(char)*100);// Client로 보낼 메시지 배열
            char temp[] ="Hello, Client, this is my reply for your message No.";
            strcpy(toClient,temp); 
            strcat(toClient,(char*)fd_array[i][1]);
            read(c_socket_fd, fromClient ,sizeof(fromClient));
            printf("From Client Message: %s\n",fromClient);
            printf("Now sending Message To Client\n");
            write(c_socket_fd, toClient, sizeof(toClient));
            flag++;
        }
    }
    }
}
close(c_socket_fd);
return 0;
}
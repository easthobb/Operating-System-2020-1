#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#include <unistd.h>


#define PORT 10829
int main(){

int clientSocket;
struct sockaddr_in server_address;
int str_len;

/* 본 코드는 fork()를 통해 총 4개의 프로세스를 생성하고 실행하며 구조는 다음과 같다.*/
/* P - (P-C1) -(P-C1-C3)*/
/* |                    */
/* (P-C2)               */

pid_t pid; // PID 선언
pid = fork();
if(pid == -1)
{ //-1 이면 fork생성 에러
    printf("can't fork, erro\n");
	exit(0);
}

if(pid == 0){ // P-C1이 실행하는 부분
    
    pid=fork();
    
    if(pid>0){ //P-C1가 실행하는 부분

    /*PROCESS 별 반복 부분-함수화 요망*/
    int PID_NUM = getpid(); // PID번호를 저장하는 변수

    printf("I AM P-C1 PROCESS MY PID IS :%d\n",PID_NUM);
    /*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/ 
    clientSocket=socket(PF_INET, SOCK_STREAM, 0);
    /*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/
    memset(&server_address, 0,sizeof(server_address));
    
    /*server_address 에 서버의 주소 정보 대입*/ 
    server_address.sin_family=AF_INET;//IPv4 채택
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); //IP 주소입력(localhost)
    server_address.sin_port=htons(PORT);//포트번호 입력

    //입력된 정보에 해당하는 서버에 접속 시도 실패시 프로세스 종료
    if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
    {
        printf("sorry, connection failed! exit this process:%d\n",PID_NUM);
        return 0;
    }
    else{ //연결에 성공했을 경우
        for(int i = 0 ; i<5 ; i++){ // 메시지에 대해 5번 수행
            char * toServer = malloc(sizeof(char)*100);
            char temp[] = "Hello, Server this is message No." ;//서버에 보낼 문자열
            char fromServer[100];
            strcpy(toServer,temp); //임시변수에 들은 문자열 복사
            strcat(toServer,(char*)i);//서버에 보낼 문자열에 sequence adding
            strcat(toServer,"from"); //from adding
            strcat(toServer,(char*)PID_NUM);//PID_NUM adding

            /*toServer 문자열을 server로 쏩니다*/
            printf("Client[PID:%d] now sending to Server\n",PID_NUM);
            write(clientSocket,toServer,sizeof(toServer));
            read(clientSocket, fromServer, sizeof(fromServer));
            printf("Client[PID:%d] got message to Server%s\n",PID_NUM,fromServer);
            free(toServer);  

        }

    }

    sleep(3);  

    }
    else{//P-C1-C3가 실행하는 부분 
 
    /*PROCESS 별 반복 부분-함수화 요망*/
    int PID_NUM = getpid(); // PID번호를 저장하는 변수

    printf("I AM P-C1-C3 PROCESS MY PID IS :%d\n",PID_NUM);
    /*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/ 
    clientSocket=socket(PF_INET, SOCK_STREAM, 0);
    /*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/
    memset(&server_address, 0,sizeof(server_address));
    
    /*server_address 에 서버의 주소 정보 대입*/ 
    server_address.sin_family=AF_INET;//IPv4 채택
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); //IP 주소입력(localhost)
    server_address.sin_port=htons(PORT);//포트번호 입력

    //입력된 정보에 해당하는 서버에 접속 시도 실패시 프로세스 종료
    if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
    {
        printf("sorry, connection failed! exit this process:%d\n",PID_NUM);
        return 0;
    }
    else{ //연결에 성공했을 경우
        for(int i = 0 ; i<5 ; i++){ // 메시지에 대해 5번 수행
            char * toServer = malloc(sizeof(char)*100);
            char temp[] = "Hello, Server this is message No." ;//서버에 보낼 문자열
            char fromServer[100];
            strcpy(toServer,temp); //임시변수에 들은 문자열 복사
            strcat(toServer,(char*)i);//서버에 보낼 문자열에 sequence adding
            strcat(toServer,"from"); //from adding
            strcat(toServer,(char*)PID_NUM);//PID_NUM adding

            /*toServer 문자열을 server로 쏩니다*/
            printf("Client[PID:%d] now sending to Server\n",PID_NUM);
            write(clientSocket,toServer,sizeof(toServer));
            read(clientSocket, fromServer, sizeof(fromServer));
            printf("Client[PID:%d] got message to Server%s\n",PID_NUM,fromServer); 
            free(toServer); 

        }

    }
    sleep(1);  
    }

}
else{ // P1이 실행하는 부분
    
    pid=fork();
    
    if(pid==0){ //P-C2 가 실행하는 부분

    /*PROCESS 별 반복 부분-함수화 요망*/
    int PID_NUM = getpid(); // PID번호를 저장하는 변수

    printf("I AM P-C2 PROCESS MY PID IS :%d\n",PID_NUM);
    /*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/ 
    clientSocket=socket(PF_INET, SOCK_STREAM, 0);
    /*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/
    memset(&server_address, 0,sizeof(server_address));
    
    /*server_address 에 서버의 주소 정보 대입*/ 
    server_address.sin_family=AF_INET;//IPv4 채택
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); //IP 주소입력(localhost)
    server_address.sin_port=htons(PORT);//포트번호 입력

    //입력된 정보에 해당하는 서버에 접속 시도 실패시 프로세스 종료
    if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
    {
        printf("sorry, connection failed! exit this process:%d\n",PID_NUM);
        return 0;
    }
    else{ //연결에 성공했을 경우
        for(int i = 0 ; i<5 ; i++){ // 메시지에 대해 5번 수행
            char * toServer = malloc(sizeof(char)*100);
            char temp[] = "Hello, Server this is message No." ;//서버에 보낼 문자열
            char fromServer[100];
            strcpy(toServer,temp); //임시변수에 들은 문자열 복사
            strcat(toServer,(char*)i);//서버에 보낼 문자열에 sequence adding
            strcat(toServer,"from"); //from adding
            strcat(toServer,(char*)PID_NUM);//PID_NUM adding

            /*toServer 문자열을 server로 쏩니다*/
            printf("Client[PID:%d] now sending to Server\n",PID_NUM);
            write(clientSocket,toServer,sizeof(toServer));
            read(clientSocket, fromServer, sizeof(fromServer));
            printf("Client[PID:%d] got message to Server%s\n",PID_NUM,fromServer);
            free(toServer);  

        }

    }

    sleep(3);  

    }
    else{// 찐 P1이 실행하는 부분
    
    /*PROCESS 별 반복 부분-함수화 요망*/
    int PID_NUM = getpid(); // PID번호를 저장하는 변수

    printf("I AM P1 PROCESS MY PID IS :%d\n",PID_NUM);
    /*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/ 
    clientSocket=socket(PF_INET, SOCK_STREAM, 0);
    /*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/
    memset(&server_address, 0,sizeof(server_address));
    
    /*server_address 에 서버의 주소 정보 대입*/ 
    server_address.sin_family=AF_INET;//IPv4 채택
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); //IP 주소입력(localhost)
    server_address.sin_port=htons(PORT);//포트번호 입력

    //입력된 정보에 해당하는 서버에 접속 시도 실패시 프로세스 종료
    if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
    {
        printf("sorry, connection failed! exit this process:%d\n",PID_NUM);
        return 0;
    }
    else{ //연결에 성공했을 경우
        for(int i = 0 ; i<5 ; i++){ // 메시지에 대해 5번 수행
            char * toServer = malloc(sizeof(char)*100);
            char temp[] = "Hello, Server this is message No." ;//서버에 보낼 문자열
            char fromServer[100];
            strcpy(toServer,temp); //임시변수에 들은 문자열 복사
            strcat(toServer,(char*)i);//서버에 보낼 문자열에 sequence adding
            strcat(toServer,"from"); //from adding
            strcat(toServer,(char*)PID_NUM);//PID_NUM adding

            /*toServer 문자열을 server로 쏩니다*/
            printf("Client[PID:%d] now sending to Server\n",PID_NUM);
            write(clientSocket,toServer,sizeof(toServer));
            read(clientSocket, fromServer, sizeof(fromServer));
            printf("Client[PID:%d] got message to Server%s\n",PID_NUM,fromServer);
            free(toServer);  

        }

    }
    sleep(4);   
    }
    }
    printf("all process is terminated ");
}

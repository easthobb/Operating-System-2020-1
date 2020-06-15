#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#define PORT 5500 // 서버가 바인딩 할 소켓 임의 지정 

/* 본 프로그램은 소켓통신을 통하여 프로세스간 채팅이 가능한 프로그램을 구현하는 것으로*/
/* 동국대학교 2020-1 운영체제 과목의 과제로 작성하였습니다. 본 프로그램은 순차적으로*/
/* 채팅이 가능하며, Bye를 입력할 경우 종료됩니다.                          */
/* 작성자 : 2015112167 김동호 */

int main(){

/*선언부*/
int s_socket_fd;//소켓 파일 디스크립터-서버의 연결
int c_socket_fd;//소켓 파일 디스크립터-클라이언트의 연결 
struct sockaddr_in server_address, client_address; // 서버의 주소와 클라이언트의 주소를 저장하는 구조체 선언
socklen_t client_address_size;// 소켓의 주소 길이를 지정하는 변수


/*클라이언트의 접속을 기다리는 서버소켓 객체 생성*/ 
s_socket_fd = socket(PF_INET, SOCK_STREAM, 0);// 소켓 디스크립터에 소켓 연결 반환
printf("Server Socket Create!!!\n");

/*서버의 IP 와 PORT 를 저장할 server_address 객체를 0으로 초기화 시킴*/ 
memset(&server_address, 0, sizeof(server_address)); // 바인딩

/*server_address 에 서버의 주소 정보 대입*/ 
server_address.sin_family=AF_INET; //IPv4 사용
server_address.sin_addr.s_addr=htonl(INADDR_ANY); //어드레스 설정옵션 임의의 할당
server_address.sin_port=htons(PORT); //지정한 포트로 바인딩
bind(s_socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)); //바인딩 실행


/*클라이언트의 접속을 기다리는 대기 모드로 전환*/ 
listen(s_socket_fd, 5); // s_socket_fd를 통한 연결을 대기, 5의 backlog 를 갖습니다.
printf("Wait Client...\n");

/* 연결이 성공할 경우*/
client_address_size = sizeof(client_address); // 클라이언트 주소 길이 지정
c_socket_fd = accept(s_socket_fd, (struct sockaddr*)&client_address,&client_address_size);
if(c_socket_fd < 0) // 연결에 문제가 생기면 종료합니다.
{
    printf("Server: accept failed.\n");
    exit(0);
}

/*클라이언트가 서버에 접속하면 접속을 수락함*/ 
printf("Client Connect!!!\n");

/* 채팅이 지속되는 동안 반복되는 와일문*/
while(1){
    
    /*클라이언트가 전달한 메시지를 읽어 들여서 fromClient에 대입*/ 
    char toClient[100];//클라이언트에게 보낼 메시지 저장 문자열 배열
    char fromClient[100];//클라이언트로부터 받은 메시지 저장 문자열 배열

    read(c_socket_fd, fromClient ,sizeof(fromClient));//소켓 디스크립터로부터 받은 문자열을 배열에 저장합니디./

    printf("From Client Message: %s\n",fromClient); // 출력합니다.
    if(strcmp("Bye",fromClient)==0)//클라이언트가 Bye를 입력했을 경우
    {   
        printf("Connection is closed.\n");
        break;
    }
    printf("\nMessage To Client:");

    scanf("%[^\n]s",toClient); //사용자에게 문자열 입력받습니다. 공백포함옵션
    fflush(stdin);

    /* 이 자리에서 Client로부터 요청받은 서비스를 수행 */
    /* Msg2Client 의 내용을 클라이언트로 전송 */

    write(c_socket_fd, toClient, sizeof(toClient)); //사용자로부터 입력받은 문자열을 디스크립터로 쏩니다.


    /*클라이언트와의 접속을 종료함*/
    if(c_socket_fd < 0)//클라이언트 소켓의 상태가 비정상일 경우
    {
        printf("Server: connection closed.\n");
        exit(0);//프로세스 종료
    }
}//와일문의 끝 

close(c_socket_fd);//클라이언트 디스크립터를 닫습니다.
return 0;
}
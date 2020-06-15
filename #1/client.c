#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#define PORT 5500 // server의 포트 5500번으로 지정

/* 본 프로그램은 소켓통신을 통하여 프로세스간 채팅이 가능한 프로그램을 구현하는 것으로*/
/* 동국대학교 2020-1 운영체제 과목의 과제로 작성하였습니다. 본 프로그램은 순차적으로*/
/* 채팅이 가능하며, Bye를 입력할 경우 종료됩니다.                          */
/* 작성자 : 2015112167 김동호 */

int main(){

int clientSocket; //클라이언트 소켓 디스크립터가 저장될 변수
struct sockaddr_in server_address; // 서버의 주소 변수가 저장될 변수


/*서버에 접속해서 데이터를 입출력 하는 클라이언트 소켓생성*/ 
clientSocket=socket(PF_INET, SOCK_STREAM, 0);
printf("Create Client Socket!!\n"); // 사용자에게 클라이언트 소켓의 동작을 알려줍니다.
/*서버의 주소 정보가 저장될 server_adress 를 0으로 초기화*/ 
memset(&server_address, 0,sizeof(server_address));
/*server_address 에 서버의 주소 정보 대입*/ 
server_address.sin_family=AF_INET; //IPv4 옵션 사용
server_address.sin_addr.s_addr=inet_addr("127.0.0.1"); //IP 입력, 여기서는 localhost 입력합니다.
server_address.sin_port=htons(PORT);//포트번호(5500)을 대입해줍니다.

/*서버에 접속시도*/
if(connect(clientSocket, (struct sockaddr*)&server_address, sizeof(server_address))==-1)
{
    printf("sorry, connection failed!");//실패할 경우 프로세스 종료.
    exit(0);
}
printf("Connect to Server is success!!\n");

/*채팅이 지속되는 동안 반복되는 while 문*/
while(1){

    char toServer[100]; //server로 보낼 메시지를 저장하는 문자열 배열
    char fromServer[100];//server로 부터 받을 메시지를 저장하는 문자열 배열 

    printf("Enter Server Message want to send (Bye will be closed connection): ");
    scanf("%[^\n]s",toServer); //toServer 배열에 문자열을 공백을 포함하여 저장합니다.
    fflush(stdin); // 사용자 표준 입력 버퍼를 비웁니다. 
    toServer[99]='\0'; //배열의 마지막은 공백 문자로 채워줍니다. 배열의 통일성을 위해 

    if(strcmp(toServer,"Bye")==0) //사용자가 Bye라고 입력할 경우
    {
        printf("connection is closing. thx you!\n"); //사용자에게 종료 메시지를 보낸 후
        write(clientSocket,toServer,sizeof(toServer)); //마지막으로 서버에게 Bye 보냅니다.
        break;//while문 탈출
    }
    /* 사용자가 정상적인 문자열을 입력했을 경우*/
    write(clientSocket,toServer,sizeof(toServer));

    /*서버에서 보내온 메시지를 fromServer 에 저장*/ 
    read(clientSocket, fromServer, sizeof(fromServer)); 
    printf("From Server Message: %s\n",fromServer);

}
//소켓을 닫습니다.
close(clientSocket); 

return 0;
}
#include <stdio.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <string.h> 
#include <sys/socket.h>
#include <unistd.h>
#define PORT 55000

int main(){

int s_socket_fd; 
int c_socket_fd;
struct sockaddr_in server_address, client_address;
socklen_t client_address_size;
char Msg2Client[]="Hello Client!!\n"; 
char Msg2Server[100];
char fromClient[100];
char toClient[100];

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

/*클라이언트의 접속을 기다리는 대기 모드로 전환*/ 
listen(s_socket_fd, 5);
printf("Wait Client...\n");
client_address_size = sizeof(client_address);

/*클라이언트가 서버에 접속하면 접속을 수락함*/
c_socket_fd = accept(s_socket_fd, (struct sockaddr*)&client_address,&client_address_size); 
printf("Client Connect!!!\n");

/*클라이언트가 전달한 메시지를 읽어 들여서 fromClient에 대입*/ 
read(c_socket_fd, Msg2Server ,sizeof(fromClient));
printf("From Client Message: %s\n",Msg2Server);

/* 이 자리에서 Client로부터 요청받은 서비스를 수행 */
/* Msg2Client 의 내용을 클라이언트로 전송 */ 
write(c_socket_fd, Msg2Client, sizeof(toClient)); 
printf("Message To Client: %s\n",Msg2Client);
/*클라이언트와의 접속을 종료함*/ 
close(c_socket_fd);
return 0;
}
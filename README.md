# Operating-System-2020-1
this repo is for Assignment on OS class,
작성자 : 2015112167 컴퓨터공학 김동호
## #1 is for simple chating program that can conect single server and client.
*note Scenario - 수준 (1)

- 하나의 서버와 하나의 클라이언트를 갖는다. 단, 서버와 클라이언트는 각각 서로 다른 포트를 사용한다.

 ### client.c

 - 클라이언트는 서버에게 “채팅”을 위한 문자열을 발송한다.
 - 서버에게 문자열을 발송한 후, 서버로부터 문자열을 수신한다.
 - 위의 두 단계를 “채팅”이 끝날 때까지 반복한다.
 - “채팅”을 마칠 때에는, “Bye”라는 문자열을 마지막으로 보낸 후, 소켓을 닫아 “채팅"을 종료한다.

 ### server.c

 - 클라이언트로부터 “채팅”을 위한 문자열을 수신한다.
 - 클라이언트로부터 문자열을 수신한 후, 클라이언트에게 문자열을 발송한다.
 - 위의 두 단계를 “채팅”이 끝날 때까지 반복한다.
 - 클라이언트로부터 “Bye”라는 문자열을 받으면, 별도의 문자열 송신 없이 소켓을 닫아 “채팅”을 종료한다.

## #2 is for implemeting multiclient handling server and client making child process
- 하나의 서버와 4개의 클라이언트를 갖는다. 단, 서버와 각 클라이언트들은 서로 다른 포트를 사용한다.

### client.c
- 클라이언트에는 처음에는 하나의 프로세스(P)가 존재한다.
- P는 하나의 자식 프로세스(P-C1)를 생성한다.
- P와 P-C1은 각각 하나씩의 새로운 자식 프로세스(P-C2, P-C1-C3)를 생성한다. 따라서 모두 4개의 프로세스가 동일한 기능을 실행한다.
- 각 클라이언트는 모두 5회씩 자기 자신의 pid를 포함한 다음과 같은 메시지를 서버에게 전송한다.

    '''
    Hello Server, this is message No.0 from 1234
    '''
- 위에서 0의 값은 메시지의 순서이며, 각 클라이언트는 0부터 5까지 5개의 메시지를 보낸다.
- 위에서 1234 자리에는 각 클라이언트의 PID 가 들어간다.
- 각 클라이언트는 각 메시지를 전송한 후 서버로부터 메시지를 받았다는 응답을 수신한 후 다음 메시지를 전송한다.
- 5회의 메시지 전송과 그에 따르는 5회의 회신을 받으면 각 클라이언트는 실행을 종료한다.

### server.c

- 서버에는 하나의 프로세스가 존재한다.
- 모두 10개의 backlog를 갖는다.
- 클라이언트로부터 메시지가 도착하면 이를 읽어 들인 후 다음과 같은 메시지를 작성하여 보낸다
    
    '''
     Hello Client, this is my reply for your message No. 0
    '''
- 위에서 0의 값은 각 클라이언트가 보낸 메시지의 순서이며, 각 클라이언트 별로 0부터 4까지의 5개의 메시지에 대한 회신을 전송한다.
- 모두 20개의 메시지를 처리한 후 연결을 종료한다.

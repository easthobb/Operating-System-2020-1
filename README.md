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




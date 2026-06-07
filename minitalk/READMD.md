# minitalk/README.md

# minitalk

UNIX Signal을 이용해 client와 server가 문자열 메시지를 주고받는 IPC 프로젝트입니다.

`SIGUSR1`, `SIGUSR2` 두 가지 signal만 사용해 문자를 bit 단위로 전송하고, server에서 다시 문자열로 복원하는 구조를 구현했습니다.

---

## Tech Stack


| Category | Stack            |
| -------- | ---------------- |
| Language | C                |
| OS       | Linux / UNIX     |
| IPC      | UNIX Signal      |
| Signal   | SIGUSR1, SIGUSR2 |
| Build    | Makefile         |


---

## Project Goal

client가 server의 PID를 이용해 문자열을 전송하면, server는 signal을 bit 단위로 수신하여 원래 문자열을 출력합니다.

```text
Client → bit encoding → SIGUSR1 / SIGUSR2 → Server → bit decoding → Message
```

---

## Main Features

- server PID 출력
- client에서 server PID와 메시지 입력
- 문자 데이터를 bit 단위로 분해
- `SIGUSR1`, `SIGUSR2`를 이용한 bit 전송
- server에서 bit를 조립해 문자로 복원
- null character 수신 시 메시지 종료
- ACK 흐름을 통한 송수신 안정성 개선

---

## Signal Mapping


| Signal    | Meaning |
| --------- | ------- |
| `SIGUSR1` | bit 0   |
| `SIGUSR2` | bit 1   |


예시:

```text
'A' = 01000001
```

client는 각 bit를 signal로 변환해 server에 보냅니다.

---

## Implementation Flow

### Server

1. 실행 시 자신의 PID 출력
2. signal handler 등록
3. signal 수신
4. bit를 누적하여 char 생성
5. 8bit 수신 시 문자 출력
6. null character 수신 시 메시지 종료 처리

### Client

1. server PID 입력
2. 전송할 문자열 입력
3. 문자열의 각 문자를 bit 단위로 분해
4. bit 값에 따라 signal 전송
5. 필요한 경우 ACK 대기

---

## What I Learned

- UNIX signal 기반 IPC 구조
- process ID를 이용한 프로세스 간 통신
- bit 연산과 문자 인코딩
- signal handler 사용 시 주의점
- 비동기 이벤트 처리 방식
- 통신 속도와 안정성의 trade-off

---

## How to Build

```bash
make
```

---

## How to Run

Terminal 1:

```bash
./server
```

출력 예시:

```text
Server PID: 12345
```

Terminal 2:

```bash
./client 12345 "hello"
```

Server 출력:

```text
hello
```

---

## Portfolio Point

이 프로젝트는 제한된 통신 수단을 이용해 데이터를 전송하는 구조를 구현한 경험입니다.

자동차 SW/System 관점에서는 **송신자, 수신자, 데이터 단위, ACK, 통신 흐름 설계**를 이해하는 기초 경험으로 연결됩니다.

---


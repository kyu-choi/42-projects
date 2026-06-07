# 42-projects

42 Seoul 과정에서 수행한 C/C++ 기반 시스템 프로그래밍 프로젝트 모음입니다.
메모리 관리, 자료구조, 프로세스, 스레드, IPC, 네트워크, 그래픽, Makefile 기반 빌드 경험을 정리했습니다.

이 저장소는 단순 과제 제출물이 아니라, **C 언어 기반 저수준 구현 능력과 Linux 환경에서의 문제 해결 경험**을 보여주기 위한 포트폴리오 저장소입니다.

---

## Tech Stack

| Category         | Stack                                                                                 |
| ---------------- | ------------------------------------------------------------------------------------- |
| Language         | C, C++                                                                                |
| Build            | Makefile                                                                              |
| OS / Environment | Linux, Ubuntu, Virtual Machine                                                        |
| Tools            | gcc, clang, gdb, valgrind, Git                                                        |
| Core Topics      | Memory Management, Process, Thread, Mutex, IPC, Parsing, Algorithm, Network, Graphics |

---

## Project Summary

| Project       | Core Concept                        | What I Implemented              | Portfolio Point       |
| ------------- | ----------------------------------- | ------------------------------- | --------------------- |
| Libft         | C Standard Library Reimplementation | 문자열, 메모리, 리스트 함수 구현             | 포인터, 메모리, 자료구조 기초     |
| ft_printf     | Variadic Arguments, Format Parsing  | `printf` 일부 기능 재구현              | 포맷 파싱, 모듈화, 예외 처리     |
| get_next_line | File Descriptor, Buffer Management  | fd별 라인 단위 입력 처리                 | 동적 메모리 관리, 버퍼 처리      |
| push_swap     | Stack, Sorting Optimization         | 제한된 명령어 기반 스택 정렬 구현             | 알고리즘 최적화, 자료구조 설계     |
| minitalk      | UNIX Signal IPC                     | `SIGUSR1`, `SIGUSR2` 기반 메시지 송수신 | 프로세스 간 통신, ACK 흐름     |
| Philosophers  | Thread, Mutex, Deadlock             | 식사하는 철학자 문제 구현                  | 동시성 제어, 데드락/기아 상태 방지  |
| minishell     | Process, Pipe, Redirection, Parsing | shell 명령어 파싱 및 실행               | 프로세스 제어, fd 관리, 파싱 구조 |
| so_long       | 2D Game, Map Validation             | 맵 검증, BFS, 이벤트 처리               | 상태 관리, 그래픽 이벤트 처리     |
| miniRT        | Ray Tracing, Vector Math            | 기본 ray tracing 렌더링 구조 구현        | 수학적 모델링, 구조화          |
| Cpp-Module    | C++ OOP                             | 클래스, 상속, 다형성, 예외 처리 학습          | 객체지향 설계 기초            |
| Born2beroot   | Linux System Administration         | VM, sudo, SSH, UFW, 사용자 정책 설정   | Linux 운영, 보안 설정       |
| NetPractice   | Network, Subnetting                 | IP, subnet, routing 문제 해결       | 네트워크 주소 체계 이해         |

---

## Key Projects

### 1. push_swap

제한된 명령어 집합만으로 스택 A의 숫자를 정렬하는 알고리즘 프로젝트입니다.

#### Main Features

* 입력값 파싱 및 유효성 검사
* 중복값, 범위 초과, 비정상 입력 처리
* 스택 기반 자료구조 구현
* 좌표 압축 / index 부여
* radix sort, chunk, cost 기반 전략 실험
* 명령어 수 최적화

#### What I Learned

* 제한 조건 안에서 알고리즘을 설계하는 방법
* 자료구조 선택이 성능에 미치는 영향
* 예외 입력 처리와 메모리 해제의 중요성
* 테스트 케이스 기반 디버깅 방식

---

### 2. minitalk

UNIX signal을 이용해 client와 server가 메시지를 주고받는 IPC 프로젝트입니다.

#### Main Features

* `SIGUSR1`, `SIGUSR2`를 이용한 bit 단위 데이터 전송
* client → server 문자 송신
* server 측 bit 조립 후 문자열 출력
* ACK 흐름을 통한 송수신 안정성 개선

#### What I Learned

* 프로세스 간 통신의 기본 구조
* signal handler 사용 시 주의점
* 비동기 이벤트 기반 처리
* 제한된 통신 수단에서 데이터 흐름을 설계하는 방법

---

### 3. Philosophers

멀티스레드 환경에서 공유 자원 접근을 제어하는 동시성 프로젝트입니다.

#### Main Features

* pthread 기반 스레드 생성
* mutex를 이용한 fork 공유 자원 보호
* deadlock 방지
* starvation 상태 감시
* monitor thread를 통한 종료 조건 확인

#### What I Learned

* 스레드 간 자원 경쟁 문제
* mutex lock/unlock 순서의 중요성
* 타이밍 이슈 디버깅
* 동시성 프로그램에서 재현 어려운 버그를 추적하는 방법

---

### 4. minishell

Linux shell의 핵심 동작을 직접 구현하는 프로젝트입니다.

#### Main Features

* 명령어 파싱
* pipe 처리
* redirection 처리
* environment variable 처리
* built-in command 구현
* fork/execve 기반 프로세스 실행
* file descriptor 관리

#### What I Learned

* shell 내부 동작 구조
* 프로세스 생성과 명령 실행 흐름
* pipe와 redirection의 fd 연결 방식
* 복잡한 요구사항을 모듈 단위로 분리하는 방법

---

### 5. so_long

2D 맵 기반 게임 프로젝트입니다.

#### Main Features

* 맵 파일 파싱
* 벽, 수집 아이템, 출구, 플레이어 위치 검증
* BFS 기반 경로 유효성 검사
* 키보드 이벤트 처리
* 이동 횟수 출력
* mlx 기반 그래픽 렌더링

#### What I Learned

* 게임 상태 관리
* 맵 검증 로직 설계
* 이벤트 기반 프로그램 구조
* 그래픽 라이브러리 사용 경험

---

## Relevance to Embedded / Automotive SW

이 저장소의 프로젝트들은 임베디드 SW와 자동차 전장 SW에서 요구되는 기초 역량과 연결됩니다.

| Required Skill         | Related Projects                | Description                         |
| ---------------------- | ------------------------------- | ----------------------------------- |
| Memory Safety          | Libft, get_next_line, minishell | 포인터, 동적 할당, 해제, 예외 처리               |
| Communication Flow     | minitalk                        | signal 기반 IPC, 송수신 흐름 설계            |
| Concurrency Control    | Philosophers                    | thread, mutex, deadlock, starvation |
| Process Control        | minishell                       | fork, execve, pipe, file descriptor |
| Algorithm Optimization | push_swap                       | 제한 조건 기반 성능 개선                      |
| Linux Understanding    | Born2beroot, NetPractice        | Linux 운영, 네트워크, 보안 기초               |
| Modular Design         | ft_printf, minishell, so_long   | 기능 단위 분리와 유지보수 가능한 구조               |

자동차 전장 SW는 제한된 환경에서 안정적으로 동작하는 코드, 명확한 상태 흐름, 예외 상황 처리, 테스트 가능한 구조가 중요하다고 생각합니다.
42 프로젝트를 통해 이러한 기초 역량을 C/Linux 환경에서 반복적으로 훈련했습니다.

---

## Build & Run

각 프로젝트 폴더로 이동한 뒤 `make` 명령어로 빌드할 수 있습니다.

```bash
cd push_swap
make
./push_swap 3 2 1
```

```bash
cd minitalk
make
./server
./client <server_pid> "hello"
```

```bash
cd Philosophers
make
./philo 5 800 200 200
```

프로젝트별 실행 인자와 세부 사용법은 각 폴더의 코드와 Makefile 기준으로 확인할 수 있습니다.

---

## Debugging & Test Approach

프로젝트를 진행하며 아래 방식으로 테스트와 디버깅을 수행했습니다.

* 다양한 정상/비정상 입력 테스트
* `gdb`를 이용한 segmentation fault 추적
* `valgrind`를 이용한 memory leak 확인
* Makefile 기반 반복 빌드
* edge case 중심 테스트
* 명령어 수, 실행 흐름, 종료 조건 검증

---

## Repository Structure

```text
42-projects/
├── Born2beroot
├── Cpp-Module
├── Libft
├── NetPractice
├── Philosophers
├── ft_printf
├── get_next_line
├── miniRT
├── minishell
├── minitalk
├── push_swap
└── so_long
```

---

## Portfolio Focus

이 저장소에서 가장 중점적으로 보여주고 싶은 역량은 다음과 같습니다.

1. C 언어 기반 저수준 구현 능력
2. Linux 환경에서의 프로세스, 스레드, 파일 디스크립터 이해
3. 메모리 관리와 예외 처리
4. 제한 조건 안에서의 알고리즘 최적화
5. 통신, 동시성, 파싱 등 시스템 SW 기초 역량
6. 문제를 작은 모듈로 나누어 구현하는 설계 능력

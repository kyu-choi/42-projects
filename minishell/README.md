# minishell/README.md

# minishell

Linux shell의 핵심 기능을 직접 구현하는 시스템 프로그래밍 프로젝트입니다.

명령어 파싱, pipe, redirection, environment variable, built-in command, process control을 구현하며 shell 내부 동작 구조를 학습했습니다.

---

## Tech Stack

| Category    | Stack                          |
| ----------- | ------------------------------ |
| Language    | C                              |
| OS          | Linux / UNIX                   |
| System Call | fork, execve, pipe, dup2, wait |
| Parsing     | Tokenizing, Syntax Analysis    |
| Build       | Makefile                       |

---

## Project Goal

사용자가 입력한 명령어를 parsing한 뒤, 실제 Linux shell처럼 명령을 실행합니다.

예시:

```bash
echo hello | grep h > result.txt
```

이 입력을 token 단위로 분석하고, pipe와 redirection을 적용한 뒤 child process에서 명령어를 실행합니다.

---

## Main Features

* prompt 출력
* 명령어 입력 처리
* quote 처리
* environment variable 확장
* pipe 처리
* input/output redirection 처리
* built-in command 구현
* external command 실행
* signal 처리
* exit status 관리

---

## Built-in Commands

| Command  | Description |
| -------- | ----------- |
| `echo`   | 문자열 출력      |
| `cd`     | 디렉터리 이동     |
| `pwd`    | 현재 경로 출력    |
| `export` | 환경변수 추가/수정  |
| `unset`  | 환경변수 제거     |
| `env`    | 환경변수 출력     |
| `exit`   | shell 종료    |

---

## Shell Execution Flow

```text
Input
→ Lexer
→ Parser
→ Command Table
→ Pipe / Redirection Setup
→ fork
→ execve or builtin
→ wait
→ exit status update
```

---

## What I Learned

* shell 내부 동작 방식
* command parsing 구조
* process 생성과 실행 흐름
* pipe와 file descriptor 연결 방식
* redirection 처리
* signal 처리
* 복잡한 요구사항을 모듈 단위로 분리하는 방법
* 팀 프로젝트에서 역할 분담과 인터페이스 설계의 중요성

---

## How to Build

```bash
make
```

---

## How to Run

```bash
./minishell
```

사용 예시:

```bash
minishell$ echo hello
minishell$ ls -l | grep README
minishell$ echo test > out.txt
minishell$ cat < out.txt
```

---

## Portfolio Point

이 프로젝트는 단순 명령 실행이 아니라, **입력 파싱 → 명령 구조화 → 프로세스 실행 → fd 제어 → 종료 상태 관리**까지 이어지는 시스템 프로그램의 전체 흐름을 구현한 경험입니다.

임베디드/자동차 SW 관점에서는 복잡한 요구사항을 기능 단위로 분해하고, 명확한 인터페이스를 가진 모듈로 나누는 설계 경험과 연결됩니다.

---

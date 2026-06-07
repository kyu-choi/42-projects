# get_next_line/README.md

# get_next_line

파일 디스크립터에서 한 줄씩 문자열을 읽어오는 함수를 구현하는 프로젝트입니다.

버퍼 관리, static 변수, 동적 메모리 처리, 여러 fd 동시 처리 방식을 학습했습니다.

---

## Tech Stack

| Category    | Stack                                    |
| ----------- | ---------------------------------------- |
| Language    | C                                        |
| System Call | read                                     |
| Core Topic  | File Descriptor, Buffer, Static Variable |
| Build       | Makefile                                 |

---

## Project Goal

`get_next_line(fd)`를 호출할 때마다 파일 디스크립터에서 다음 한 줄을 반환합니다.

```c
char *line = get_next_line(fd);
```

---

## Main Features

* `read` 기반 파일 입력 처리
* BUFFER_SIZE 단위로 읽기
* 개행 문자 기준 라인 분리
* static buffer 관리
* EOF 처리
* 여러 file descriptor 처리

---

## What I Learned

* file descriptor 개념
* buffer 단위 입력 처리
* static 변수의 생명주기
* 동적 메모리 할당과 해제
* edge case 처리

---

## How to Build

```bash
make
```

---

## Portfolio Point

이 프로젝트는 입력 스트림을 안정적으로 처리하기 위한 버퍼 관리 프로젝트입니다.
파일, 표준 입력, 여러 fd를 다루며 C의 메모리 관리와 시스템 콜 사용 경험을 쌓았습니다.

---

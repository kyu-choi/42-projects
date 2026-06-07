# ft_printf/README.md

# ft_printf

C 표준 함수 `printf`의 일부 기능을 직접 구현하는 프로젝트입니다.

가변 인자 처리, 포맷 문자열 파싱, 타입별 출력 함수를 구현했습니다.

---

## Tech Stack

| Category   | Stack                       |
| ---------- | --------------------------- |
| Language   | C                           |
| Build      | Makefile                    |
| Core Topic | Variadic Arguments, Parsing |

---

## Main Features

* 가변 인자 처리
* format specifier 파싱
* 문자, 문자열, 정수, 포인터 출력
* 16진수 출력
* 출력 문자 수 반환

---

## Supported Specifiers

| Specifier   | Description      |
| ----------- | ---------------- |
| `%c`        | character        |
| `%s`        | string           |
| `%p`        | pointer address  |
| `%d` / `%i` | signed integer   |
| `%u`        | unsigned integer |
| `%x` / `%X` | hexadecimal      |
| `%%`        | percent sign     |

---

## What I Learned

* `stdarg.h` 기반 가변 인자 처리
* 포맷 문자열 파싱 구조
* 타입별 출력 함수 분리
* 재귀/반복 기반 숫자 출력
* 예외 입력 처리

---

## How to Build

```bash
make
```

---

## Portfolio Point

이 프로젝트는 단순 출력 함수 구현이 아니라, **포맷 문자열을 해석하고 타입에 맞는 동작으로 분기하는 파싱 구조**를 경험한 프로젝트입니다.

---

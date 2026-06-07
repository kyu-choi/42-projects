# Libft/README.md

# Libft

C 표준 라이브러리의 일부 함수를 직접 구현하는 프로젝트입니다.

문자열 처리, 메모리 처리, 리스트 자료구조를 구현하며 C 언어의 포인터, 메모리, 함수 분리 방식을 학습했습니다.

---

## Tech Stack

| Category       | Stack                   |
| -------------- | ----------------------- |
| Language       | C                       |
| Build          | Makefile                |
| Data Structure | Linked List             |
| Core Topic     | Pointer, Memory, String |

---

## Main Features

* 문자열 처리 함수 구현
* 메모리 처리 함수 구현
* 문자 판별/변환 함수 구현
* 리스트 자료구조 함수 구현
* 정적 라이브러리 `libft.a` 생성

---

## Implemented Function Categories

| Category  | Examples                                            |
| --------- | --------------------------------------------------- |
| Character | `ft_isalpha`, `ft_isdigit`, `ft_toupper`            |
| String    | `ft_strlen`, `ft_strlcpy`, `ft_strjoin`, `ft_split` |
| Memory    | `ft_memset`, `ft_memcpy`, `ft_calloc`               |
| List      | `ft_lstnew`, `ft_lstadd_back`, `ft_lstclear`        |

---

## What I Learned

* C 포인터와 주소 연산
* 문자열과 메모리의 차이
* 동적 메모리 할당과 해제
* Makefile을 통한 정적 라이브러리 생성
* 재사용 가능한 함수 단위 설계

---

## How to Build

```bash
make
```

생성 결과:

```text
libft.a
```

---

## Portfolio Point

Libft는 이후 C 프로젝트들의 기반이 되는 개인 라이브러리입니다.
C 언어의 기본기, 메모리 관리, 함수 모듈화 역량을 보여주는 프로젝트입니다.

---

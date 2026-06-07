# push_swap/[README.md](http://README.md)

# push_swap

제한된 명령어 집합을 사용해 스택 A의 정수들을 오름차순으로 정렬하는 알고리즘 최적화 프로젝트입니다.

이 프로젝트에서는 입력 파싱, 예외 처리, 좌표 압축, 스택 자료구조, 정렬 전략 비교를 통해 **제한 조건 안에서 효율적인 알고리즘을 설계하는 경험**을 했습니다.

---

## Tech Stack


| Category       | Stack                                            |
| -------------- | ------------------------------------------------ |
| Language       | C                                                |
| Build          | Makefile                                         |
| Data Structure | Stack, Linked List / Array                       |
| Algorithm      | Radix Sort, Chunk Strategy, Cost-based Insertion |
| Tools          | gcc, gdb, valgrind                               |


---

## Project Goal

주어진 정수 목록을 두 개의 스택 `A`, `B`와 제한된 명령어만 사용해 정렬합니다.

사용 가능한 명령어는 다음과 같습니다.


| Command               | Description             |
| --------------------- | ----------------------- |
| `sa` / `sb` / `ss`    | 스택 상단 두 원소 교환           |
| `pa` / `pb`           | 한 스택의 top을 다른 스택으로 push |
| `ra` / `rb` / `rr`    | 스택을 위로 rotate           |
| `rra` / `rrb` / `rrr` | 스택을 아래로 reverse rotate  |


---

## Main Features

- 입력값 파싱 및 유효성 검사
- 중복값 검사
- `int` 범위 초과 검사
- 좌표 압축을 통한 index 부여
- 스택 초기화 및 명령어 함수 구현
- radix sort 기반 정렬
- chunk 전략 실험
- cost 기반 재삽입 전략 실험
- checker 프로그램을 통한 결과 검증

---

## Implementation Details

### 1. Input Parsing

입력 문자열을 정수 배열 또는 리스트로 변환하고, 다음 예외를 검사했습니다.

- 숫자가 아닌 문자
- 중복 숫자
- `int` 범위 초과
- 빈 문자열
- 공백만 있는 입력

### 2. Index Compression

실제 숫자 값 대신 정렬 순서를 기준으로 index를 부여했습니다.

예시:

```text
Input:  42 -3 10
Index:   2  0  1

```

이를 통해 radix sort와 같은 비트 기반 정렬 전략을 쉽게 적용할 수 있었습니다.

### 3. Sorting Strategy

처음에는 단순 정렬 방식으로 접근한 뒤, 입력 크기에 따라 다른 전략을 적용했습니다.


| Input Size | Strategy                      |
| ---------- | ----------------------------- |
| 2개         | swap                          |
| 3개         | hard-coded sorting            |
| 5개 이하      | 작은 값 push 후 정렬                |
| 100개 이상    | radix / chunk / cost strategy |


---

## What I Learned

- 제한된 명령어만으로 문제를 해결하는 알고리즘 설계 방식
- 스택 자료구조의 동작 원리
- 입력 예외 처리의 중요성
- 좌표 압축을 통한 문제 단순화
- 명령어 수 최적화 사고
- 메모리 누수 점검과 디버깅 습관

---

## How to Build

```bash
make

```

---

## How to Run

```bash
./push_swap 3 2 1

```

예상 출력:

```text
sa
rra

```

---

## Test Example

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG

```

예상 결과:

```text
OK

```

---

## Portfolio Point

이 프로젝트는 단순 정렬 구현이 아니라, **제한 조건 안에서 자료구조와 알고리즘을 선택하고 최적화하는 경험**을 보여줍니다.

임베디드/자동차 SW 관점에서는 제한된 자원과 명확한 규칙 안에서 안정적으로 동작하는 로직을 설계하는 훈련과 연결됩니다.

---


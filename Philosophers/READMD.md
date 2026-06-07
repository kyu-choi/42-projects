# Philosophers/README.md

# Philosophers

멀티스레드 환경에서 공유 자원 접근 문제를 해결하는 동시성 프로그래밍 프로젝트입니다.

식사하는 철학자 문제를 통해 thread, mutex, deadlock, starvation, timing issue를 다뤘습니다.

---

## Tech Stack


| Category        | Stack              |
| --------------- | ------------------ |
| Language        | C                  |
| Thread          | pthread            |
| Synchronization | mutex              |
| Build           | Makefile           |
| Tools           | gcc, gdb, valgrind |


---

## Project Goal

여러 철학자가 원형 테이블에 앉아 있고, 각 철학자는 양쪽의 fork를 모두 잡아야 식사할 수 있습니다.

각 철학자는 다음 상태를 반복합니다.

```text
think → take fork → eat → sleep → think
```

모든 철학자가 동시에 fork를 잡으려 할 때 발생할 수 있는 deadlock과 starvation을 방지해야 합니다.

---

## Main Features

- pthread 기반 철학자 thread 생성
- mutex 기반 fork 공유 자원 보호
- 식사 시간, 수면 시간, 사망 시간 관리
- monitor thread를 통한 상태 감시
- deadlock 방지
- starvation 방지
- 종료 조건 처리
- 로그 출력 동기화

---

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

예시:

```bash
./philo 5 800 200 200
```


| Argument                                    | Description             |
| ------------------------------------------- | ----------------------- |
| `number_of_philosophers`                    | 철학자 수                   |
| `time_to_die`                               | 식사하지 않으면 죽는 시간          |
| `time_to_eat`                               | 식사 시간                   |
| `time_to_sleep`                             | 수면 시간                   |
| `number_of_times_each_philosopher_must_eat` | 선택 인자, 각 철학자가 먹어야 하는 횟수 |


---

## Synchronization Strategy

공유 자원은 mutex로 보호했습니다.


| Shared Resource | Protection  |
| --------------- | ----------- |
| Forks           | fork mutex  |
| Print log       | print mutex |
| Death flag      | state mutex |
| Last meal time  | meal mutex  |


---

## What I Learned

- thread 생성과 종료 흐름
- mutex lock/unlock 순서의 중요성
- deadlock 발생 조건
- starvation 방지 방법
- millisecond 단위 시간 관리
- 동시성 프로그램의 디버깅 어려움
- 공유 데이터 접근 시 race condition 방지

---

## How to Build

```bash
make
```

---

## How to Run

```bash
./philo 5 800 200 200
```

---

## Test Cases

```bash
./philo 1 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
```

---

## Portfolio Point

이 프로젝트는 동시성 환경에서 공유 자원을 안정적으로 제어하는 경험을 보여줍니다.

자동차/임베디드 SW에서도 여러 task 또는 thread가 공유 자원에 접근하는 상황이 발생할 수 있기 때문에, mutex와 timing issue를 다룬 경험은 중요한 기초 역량입니다.

---


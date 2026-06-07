# so_long/README.md

# so_long

2D 맵 기반 게임을 구현하는 그래픽 프로젝트입니다.

맵 파일을 파싱하고, 플레이어 이동, 아이템 수집, 출구 도달 조건, 경로 유효성 검사를 구현했습니다.

---

## Tech Stack

| Category  | Stack          |
| --------- | -------------- |
| Language  | C              |
| Graphics  | MiniLibX       |
| Algorithm | BFS / DFS      |
| Build     | Makefile       |
| Input     | Keyboard Event |

---

## Project Goal

`.ber` 맵 파일을 읽어 2D 게임 맵을 구성하고, 플레이어가 모든 아이템을 수집한 뒤 출구로 이동하면 게임을 종료합니다.

---

## Map Elements

| Character | Meaning     |
| --------- | ----------- |
| `1`       | Wall        |
| `0`       | Empty Space |
| `P`       | Player      |
| `C`       | Collectible |
| `E`       | Exit        |

예시:

```text
111111
1P0C01
1000E1
111111
```

---

## Main Features

* `.ber` 맵 파일 파싱
* 맵 확장자 검사
* 직사각형 맵 검사
* 벽으로 둘러싸인 맵 검사
* 플레이어, 출구, 아이템 개수 검사
* BFS/DFS 기반 경로 유효성 검사
* 키보드 입력 처리
* 플레이어 이동
* 이동 횟수 출력
* 모든 아이템 수집 후 출구 진입 가능
* MiniLibX 기반 이미지 렌더링

---

## Game Flow

```text
Load map
→ Validate map
→ Render window
→ Handle keyboard input
→ Update player position
→ Collect item
→ Check exit condition
→ End game
```

---

## What I Learned

* 그래픽 이벤트 기반 프로그램 구조
* 맵 데이터 파싱과 검증
* BFS/DFS를 이용한 경로 유효성 검사
* 게임 상태 관리
* 사용자 입력 처리
* 리소스 로딩과 해제

---

## How to Build

```bash
make
```

---

## How to Run

```bash
./so_long maps/example.ber
```

---

## Portfolio Point

이 프로젝트는 그래픽 구현보다 **입력 파일 검증, 상태 관리, 이벤트 처리, 경로 탐색**이 핵심입니다.

사용자 입력과 내부 상태 변화가 연결되는 구조를 구현했다는 점에서, 상태 기반 프로그램 설계 경험으로 설명할 수 있습니다.

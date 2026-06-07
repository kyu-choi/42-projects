# miniRT/README.md

# miniRT

Ray Tracing 기법을 이용해 3D 장면을 렌더링하는 그래픽 프로젝트입니다.

카메라, 조명, 구, 평면, 원기둥 등의 객체를 수학적으로 계산하여 2D 화면에 표현합니다.

---

## Tech Stack

| Category | Stack                 |
| -------- | --------------------- |
| Language | C                     |
| Graphics | MiniLibX              |
| Math     | Vector, Ray, Geometry |
| Build    | Makefile              |

---

## Main Features

* scene file parsing
* camera 설정
* ambient light 처리
* object intersection 계산
* sphere, plane, cylinder 렌더링
* diffuse lighting
* shadow 처리
* vector 연산 유틸리티 구현

---

## Rendering Flow

```text
Scene parsing
→ Camera setup
→ Ray generation
→ Object intersection
→ Lighting calculation
→ Pixel rendering
```

---

## What I Learned

* 3D 벡터 연산
* ray-object intersection 계산
* 그래픽 렌더링 파이프라인
* 수학적 모델을 코드로 구현하는 방법
* 구조체 기반 장면 데이터 관리

---

## Portfolio Point

이 프로젝트는 그래픽 결과물뿐만 아니라, 수학적 모델을 코드 구조로 변환하는 경험을 보여줍니다.
복잡한 계산 로직을 모듈화하고 디버깅한 경험을 설명하기 좋습니다.

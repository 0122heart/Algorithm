# Dynamic Programming(DP)

분할 정복 알고리즘임
→ 부분의 최적해를 통해 전체의 최적해를 구성할 수 있음

###  방식

1. TOP-DOWN :
    1. 재귀 기반
    2. 이미 계산한 하위 문제는 저장하여 재사용
    3. 실제로 호출이 일어나기 전에는 하위 문제를 계산하지 않음 → 필요한 문제만 골라서 계산함
2. BOTTOM-UP :
    1. 반복문 기반(점화식)
    2. 모든 작은 문제를 미리 계산하여 테이블을 채워둠 →  즉, 모든 작은 문제를 최소 한 번은 계산함

### 중요

1. dp table의 각 index가 무엇을 의미하는지 생각해야함
2. 점화식이 아닌 재귀를 통해서도 dp table을 생성할 수 있음

### 문제

- 12865_평범한배낭_골드5 (https://www.acmicpc.net/problem/12865)
- 1351_무한 수열_골드5 (https://www.acmicpc.net/problem/1351)
- 1354_무한 수열2_골드5 (https://www.acmicpc.net/problem/1354)
- <25.07.28.월> 1949/우수마을/골드2(https://www.acmicpc.net/problem/1949)
- 
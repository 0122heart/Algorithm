#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> people(10001);           // 마을 주민 수
vector<int> adj[10001];              // 트리 인접 리스트
int dp[10001][2];                    // [0]: 일반 마을, [1]: 우수 마을
bool selected[10001];                // 최종 선택된 우수 마을 여부

// 트리 DP (후위 순회)
void dfs(int now, int parent) {
    dp[now][0] = 0;
    dp[now][1] = people[now];

    for (int next : adj[now]) {
        if (next == parent) continue;
        dfs(next, now);
        dp[now][0] += max(dp[next][0], dp[next][1]);
        dp[now][1] += dp[next][0]; // next는 일반 마을이어야 함
    }
}

// 선택 결과 복원 (최댓값을 이루는 경로로 우수 마을 결정)
void reconstruct(int now, int parent, bool isExcellent) {
    selected[now] = isExcellent;

    for (int next : adj[now]) {
        if (next == parent) continue;

        if (isExcellent) {
            reconstruct(next, now, false); // 자식은 반드시 일반
        } else {
            // 둘 중 큰 값으로 선택
            if (dp[next][1] > dp[next][0])
                reconstruct(next, now, true);
            else
                reconstruct(next, now, false);
        }
    }
}

// 조건 2: 일반 마을은 적어도 하나의 우수 마을과 인접해야 함
bool validate(int now, int parent) {
    bool valid = true;

    for (int next : adj[now]) {
        if (next == parent) continue;
        valid &= validate(next, now);
    }

    if (!selected[now]) {
        bool hasExcellentNeighbor = false;
        for (int next : adj[now]) {
            if (selected[next]) {
                hasExcellentNeighbor = true;
                break;
            }
        }
        if (!hasExcellentNeighbor)
            return false;
    }

    return valid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> people[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0); // 트리 DP 시작 (루트: 1)
    int answer = max(dp[1][0], dp[1][1]);

    // DP 결과 기반 선택 복원
    if (dp[1][1] > dp[1][0])
        reconstruct(1, 0, true);
    else
        reconstruct(1, 0, false);

    // 조건 2 검증
    if (!validate(1, 0)) {
        cout << "조건을 만족하는 해가 없음\n";
        return 0;
    }

    cout << answer << '\n';

    // 선택된 우수 마을 출력 (optional)
    /*
    for (int i = 1; i <= N; i++) {
        if (selected[i]) cout << i << ' ';
    }
    cout << '\n';
    */

    return 0;
}

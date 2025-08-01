#include <bits/stdc++.h>
using namespace std;

int N, start_planet;
int time_table[10][10];
int shortest_time_table[10][10];
int result = INT_MAX;
bool visited[10];

void back_tracking(int depth, int current, int total_time) {
    if (depth == N - 1) { // 모든 행성 탐사 완료
        result = min(result, total_time);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            back_tracking(depth + 1, i, total_time + shortest_time_table[current][i]);
            visited[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> start_planet;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> time_table[i][j];
        }
    }

    // 1. 최단 경로 테이블 초기화
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            shortest_time_table[i][j] = time_table[i][j];
        }
    }

    // 2. 플로이드 워셜 알고리즘
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (shortest_time_table[i][j] > shortest_time_table[i][k] + shortest_time_table[k][j]) {
                    shortest_time_table[i][j] = shortest_time_table[i][k] + shortest_time_table[k][j];
                }
            }
        }
    }

    // 3. 백트래킹으로 최소 시간 탐색
    visited[start_planet] = true;
    back_tracking(0, start_planet, 0);

    cout << result << "\n";

    return 0;
}

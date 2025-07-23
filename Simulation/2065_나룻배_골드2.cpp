#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, t, N;
    cin >> M >> t >> N;

    // 0=left, 1=right
    queue<pair<int,int>> q[2];
    vector<int> answer(N);

    for (int i = 0; i < N; i++) {
        int time;
        string dir;
        cin >> time >> dir;
        int side = (dir == "left" ? 0 : 1);
        q[side].emplace(time, i);
    }

    int now = 0;
    int side = 0;  // 배는 처음에 왼쪽(0)에 위치

    while (!q[0].empty() || !q[1].empty()) {
        // 1) 현재 쪽에 기다리는 손님이 있으면 바로 태우고 건넘
        if (!q[side].empty() && q[side].front().first <= now) {
            vector<pair<int,int>> boat;
            for (int cnt = 0; cnt < M && !q[side].empty() && q[side].front().first <= now; cnt++) {
                boat.push_back(q[side].front());
                q[side].pop();
            }
            now += t;  // 건너는 데 걸리는 시간
            for (auto &p : boat) {
                answer[p.second] = now;
            }
            side = 1 - side;
        }
        // 2) 현재 쪽에 없고, 반대쪽에 기다리는 손님이 있으면 빈 배 이동
        else if (!q[1-side].empty() && q[1-side].front().first <= now) {
            now += t;
            side = 1 - side;
        }
        // 3) 둘 다 없으면 다음 손님 도착 시각까지 대기
        else {
            int nextTime = INT_MAX;
            if (!q[0].empty()) nextTime = min(nextTime, q[0].front().first);
            if (!q[1].empty()) nextTime = min(nextTime, q[1].front().first);
            now = max(now, nextTime);
        }
    }

    // 결과 출력 (입력 순서대로)
    for (int i = 0; i < N; i++) {
        cout << answer[i] << "\n";
    }

    return 0;
}

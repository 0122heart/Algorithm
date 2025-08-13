#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int K;
    cin >> s >> K;

    // 자릿수가 1이면 스왑 자체가 불가능
    if (s.size() == 1) {
        cout << -1 << '\n';
        return 0;
    }

    // 현재 단계에서 가능한 모든 문자열 상태 집합
    unordered_set<string> current;
    current.insert(s);

    size_t n = s.length();

    for (int step = 0; step < K; step++) {
        unordered_set<string> next;

        for (const string &now : current) {
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    // 스왑 결과 맨 앞이 0이면 금지
                    if (i == 0 && now[j] == '0') continue;

                    string tmp = now;
                    swap(tmp[i], tmp[j]);
                    next.insert(tmp);
                }
            }
        }

        if (next.empty()) { // 더 진행 불가
            cout << -1 << '\n';
            return 0;
        }
        current.swap(next); // 다음 단계로 이동
    }

    // K번 스왑 후 가능한 상태들 중 최댓값
    string ans = *max_element(current.begin(), current.end(), [](const string &a, const string &b){
        // 동일 길이이므로 문자열 비교로 충분 (사전식 == 수치 비교)
        return a < b;
    });

    cout << ans << '\n';
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int row, col;
};

int n, num_guest, fuel;
int board[20][20]; // 0=빈칸, 1=벽, 2=승객
int d_row[] = {-1, 0, 0, 1};
int d_col[] = {0, -1, 1, 0};
Node taxi;
map<pair<int,int>, Node> dest_map; // 출발 -> 도착 매핑

bool in_range(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

// BFS로 승객 찾기
pair<Node,int> find_guest() {
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<tuple<int,int,int>> q;
    visited[taxi.row][taxi.col] = true;
    q.push({taxi.row, taxi.col, 0});

    vector<Node> candidates;
    int min_dist = -1;

    while (!q.empty()) {
        auto [row, col, dist] = q.front();
        q.pop();

        if (board[row][col] == 2) { // 승객 발견
            if (min_dist == -1) min_dist = dist;
            if (dist == min_dist) candidates.push_back({row, col});
            continue; // 같은 거리 내 다른 승객도 계속 탐색
        }

        for (int dir = 0; dir < 4; dir++) {
            int nr = row + d_row[dir], nc = col + d_col[dir];
            if (!in_range(nr, nc) || visited[nr][nc] || board[nr][nc] == 1) continue;
            visited[nr][nc] = true;
            q.push({nr, nc, dist + 1});
        }
    }

    if (candidates.empty()) return {{-1, -1}, -1};

    // 거리 같을 시 우선순위
    sort(candidates.begin(), candidates.end(), [](Node a, Node b) {
        if (a.row != b.row) return a.row < b.row;
        return a.col < b.col;
    });

    Node chosen = candidates[0];
    return {chosen, min_dist};
}

// BFS로 목적지까지 거리 계산
int go_destination(Node start, Node goal) {
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<tuple<int,int,int>> q;
    visited[start.row][start.col] = true;
    q.push({start.row, start.col, 0});

    while (!q.empty()) {
        auto [row, col, dist] = q.front();
        q.pop();
        if (row == goal.row && col == goal.col) return dist;

        for (int dir = 0; dir < 4; dir++) {
            int nr = row + d_row[dir], nc = col + d_col[dir];
            if (!in_range(nr, nc) || visited[nr][nc] || board[nr][nc] == 1) continue;
            visited[nr][nc] = true;
            q.push({nr, nc, dist + 1});
        }
    }

    return -1; // 목적지 도달 불가
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> num_guest >> fuel;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    cin >> taxi.row >> taxi.col;
    taxi.row--;
    taxi.col--;

    for (int i = 0; i < num_guest; i++) {
        int sr, sc, er, ec;
        cin >> sr >> sc >> er >> ec;
        sr--; sc--; er--; ec--;
        board[sr][sc] = 2; // 승객 위치 표시
        dest_map[{sr, sc}] = {er, ec};
    }

    for (int i = 0; i < num_guest; i++) {
        // 1. 승객 찾기
        auto [guest_pos, dist_to_guest] = find_guest();
        if (guest_pos.row == -1 || fuel < dist_to_guest) {
            cout << -1;
            return 0;
        }

        // 이동해서 승객 태우기
        fuel -= dist_to_guest;
        taxi = guest_pos;
        board[guest_pos.row][guest_pos.col] = 0; // 승객 제거

        // 2. 목적지 이동
        Node goal = dest_map[{guest_pos.row, guest_pos.col}];
        int dist_to_dest = go_destination(taxi, goal);
        if (dist_to_dest == -1 || fuel < dist_to_dest) {
            cout << -1;
            return 0;
        }

        // 이동 후 연료 보충
        fuel -= dist_to_dest;
        fuel += dist_to_dest * 2;

        taxi = goal; // 택시 위치 갱신
    }

    cout << fuel;
    return 0;
}

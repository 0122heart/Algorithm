#include <bits/stdc++.h>
using namespace std;

int num_row, num_col;
int d_row[] = {1, 0, -1, 0}, d_col[] = {0, 1, 0, -1};
char board[50][50];
pair<int, int> record[50][50]; // {g_cnt, near_cnt}
pair<int, int> start_pos, target_pos;

bool is_in_range(int row, int col){
    return 0 <= row && row < num_row && 0 <= col && col < num_col;
}

bool is_next_to_garbage(int row, int col){
    for(int d = 0; d < 4; d++){
        int next_row = row + d_row[d];
        int next_col = col + d_col[d];
        if(!is_in_range(next_row, next_col)) continue;
        if(board[next_row][next_col] == 'g') return true;
    }
    return false;
}

void setting(){
    cin >> num_row >> num_col;
    for(int row = 0; row < num_row; row++){
        for(int col = 0; col < num_col; col++){
            record[row][col] = {INT_MAX, INT_MAX};
            cin >> board[row][col];
            if(board[row][col] == 'S') start_pos = {row, col};
            if(board[row][col] == 'F') target_pos = {row, col};
        }
    }
    // 시작점 초기 비용: g/F가 아니고, 인접에 g가 있으면 near +1
    int sr = start_pos.first, sc = start_pos.second;
    int init_near = (board[sr][sc] != 'g' && board[sr][sc] != 'F' && board[sr][sc] != 'S' && is_next_to_garbage(sr, sc)) ? 1 : 0;
    record[sr][sc] = {0, init_near};
}

void process(){
    queue<pair<int, int>> frontier;
    frontier.emplace(start_pos.first, start_pos.second);

    while(!frontier.empty()){
        auto now = frontier.front(); frontier.pop();
        int r = now.first, c = now.second;

        for(int d = 0; d < 4; d++){
            int nr = r + d_row[d];
            int nc = c + d_col[d];
            if(!is_in_range(nr, nc)) continue;

            pair<int, int> temp = record[r][c];

            // 1차: g 칸으로 이동하면 g_cnt +1
            if(board[nr][nc] == 'g') temp.first++;

            // 2차: g도 F도 아닌 칸이며, 그 칸이 g에 인접하면 near_cnt +1
            if(board[nr][nc] != 'g' && board[nr][nc] != 'F' && is_next_to_garbage(nr, nc)){
                temp.second++;
            }

            // 더 좋은 비용(사전식)이면 갱신 후 재삽입
            auto cur = record[nr][nc];
            bool better = false;
            if (temp.first < cur.first) better = true;
            else if (temp.first == cur.first && temp.second < cur.second) better = true;

            if (better) {
                record[nr][nc] = temp;
                if(board[nr][nc] != 'F') frontier.emplace(nr, nc);
            }
        }
    }

    cout << record[target_pos.first][target_pos.second].first << " " << record[target_pos.first][target_pos.second].second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    setting();
    process();
    return 0;
}

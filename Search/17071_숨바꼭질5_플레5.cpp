#include <bits/stdc++.h>
using namespace std;

int subin, target, spending = 1;
int pos_at_time[2][500001];

void fill_subin(){
    queue<pair<int, int>> frontier;
    frontier.emplace(subin, 1);
    pos_at_time[0][subin] = 0;

    while(!frontier.empty()){
        auto now = frontier.front(); frontier.pop();
        int next_time = now.second;
        int odd_or_even = next_time % 2;
        for(int next_pos : {now.first + 1, now.first - 1, 2 * now.first}){
            if(0 <= next_pos && next_pos <= 500000 && pos_at_time[odd_or_even][next_pos] == -1){
                pos_at_time[odd_or_even][next_pos] = next_time;
                frontier.emplace(next_pos, next_time + 1);
            }
        }
    }
}

void find_target(){
    int spending = 1;
    target += spending;
    while(target <= 500000){
        if(pos_at_time[spending % 2][target] != -1 && pos_at_time[spending % 2][target] <= spending){
            cout << spending;
            return;
        }
        spending++;
        target += spending;
    }
    cout << -1;
    return;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> subin >> target;
    for(int i = 0; i < 2; i++){
        fill(pos_at_time[i], pos_at_time[i] + 500001, -1);
    }

    // 최초의 위치가 같을 때
    if(subin == target){
        cout << 0;
        exit(0);
    }

    fill_subin();
    find_target();

    return 0;
}

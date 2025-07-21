#include <bits/stdc++.h>
#define LL long long
using namespace std;

unordered_map<LL, LL> u_m;
LL N, P, Q, X, Y;

LL answer(LL num){
    if(num <= 0) return 1;
    if(u_m.find(num) != u_m.end()){
        return u_m[num];
    }
    u_m[num] = answer(num / P - X) + answer(num / Q - Y);
    return u_m[num];
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> P >> Q >> X >> Y;
    u_m[0] = 1;
    if(N == 0) cout << 1;
    else cout << answer(N / P - X) + answer(N / Q - Y);
    return 0;
}

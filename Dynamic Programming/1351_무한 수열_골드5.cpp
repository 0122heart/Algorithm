#include <bits/stdc++.h>
#define LL long long
using namespace std;

unordered_map<LL, LL> u_m;
LL N, P, Q;

LL answer(LL num){
    if(u_m.find(num) != u_m.end()){
        return u_m[num];
    }
    u_m[num] = answer(num / P) + answer(num / Q);
    return u_m[num];
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> P >> Q;
    u_m[0] = 1;
    if(!N) cout << 1;
    else cout << answer(N / P) + answer(N / Q);
    return 0;
}

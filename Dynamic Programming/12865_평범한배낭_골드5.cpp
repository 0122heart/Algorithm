#include <bits/stdc++.h>
using namespace std;

int N, max_weight;
int W[101], V[101];
int DP[101][100001];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> N >> max_weight;

    // weight와 value 입력받기
    for(int i = 1; i <= N; i++){
        cin >> W[i] >> V[i];
    }

    // DP[i][j]에서
    // i는 1번째부터 i번째 물건까지 담을 때를 의미함
    // j는 최대 무게가 j일 때를 의미함
    // 최대 무게보다 물건의 무게가 클 때(j < W[i]) DP[i][j]는 DP[i - 1][j]와 같음
    // 최대 무게보다 물건의 무게가 작을 때(W[i] <= j) DP[i][j]는 i를 담을 때와 담지 않을 때 중 더 큰 value를 골라야 함
    // DP[i - 1][j - W[i]]는 i를 담을 때 최대 무게에서 W[i]만큼을 뺀 것을 최대 무게로 하여 i - 1번째까지의 물건을 담을 때의 value를 의미함
    // i * j <= 10,000,000 임으로 시간복잡도 ok

    for(int i = 1; i <= N; i++){
        for(int j = 0; j <= max_weight; j++){
            if(j < W[i]){
                DP[i][j] = DP[i - 1][j];
            }
            else{
                DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - W[i]] + V[i]);
            }
        }
    }

    cout << DP[N][max_weight];

    return 0;
}

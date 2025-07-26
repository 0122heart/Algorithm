#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num_building;
    int height[50];
    cin >> num_building;
    for(int i = 0; i < num_building; i++) cin >> height[i];

    int result = 0;
    for(int i = 0; i < num_building; i++){
        int cnt = 0;

        // 바로 왼쪽의 경우
        int p, q;

        if(0 <= i - 1){
            cnt++;
            p = height[i] - height[i - 1];
            q = 1;
        }

        for(int j = i - 2; -1 < j; j--){
            // 기울기가 감소하면 cnt ++
            if((long long)q * (height[i] - height[j]) < (long long)p * (i - j)){
                cnt++;
                p = height[i] - height[j];
                q = i - j;
            }
        }

        // 바로 오른쪽의 경우
        if(i + 1 < num_building){
            cnt++;
            p = height[i + 1] - height[i];
            q = 1;
        }

        for(int j = i + 1; j < num_building; j++){
            // 기울기가 증가하면 cnt++
            if((long long)p * (j - i) < (long long)q * (height[j] - height[i])){
                cnt++;
                p = height[j] - height[i];
                q = j - i;
            }
        }

        result = max(result, cnt);
    }

    cout << result;
    return 0;
}

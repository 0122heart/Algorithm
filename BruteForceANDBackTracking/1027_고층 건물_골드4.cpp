#include <bits/stdc++.h>
using namespace std;

int main()
{
    int num_building;
    int height[50];
    cin >> num_building;
    for(int i = 0; i < num_building; i++) cin >> height[i];

    double inclination[50][50];
    // 기준 빌딩이 i
    for(int i = 0; i < num_building; i++){
        // 비교 빌딩이 j
        for(int j = 0; j < i; j++){
            inclination[i][j] = 1.0 * (height[i] - height[j]) / (i - j);
        }
        for(int j = i + 1; j < num_building; j++){
            inclination[i][j] = 1.0 * (height[j] - height[i]) / (j - i);
        }
    }

    int result = 0;
    for(int i = 0; i < num_building; i++){
        int cnt = 0;

        // 바로 왼쪽의 경우
        double standard = DBL_MAX;

        if(0 <= i - 1){
            cnt++;
            standard = inclination[i][i - 1];
        }

        for(int j = i - 2; -1 < j; j--){
            // 기울기가 감소하면 cnt ++
            if(inclination[i][j] < standard){
                cnt++;
                standard = inclination[i][j];
            }
        }

        // 바로 오른쪽의 경우
        standard = DBL_MIN;
        if(i + 1 < num_building){
            cnt++;
            standard = inclination[i][i + 1];
        }

        for(int j = i + 1; j < num_building; j++){
            if(standard < inclination[i][j]){
                cnt++;
                standard = inclination[i][j];
            }
        }

        result = max(result, cnt);
    }

    cout << result;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int num_sequence, input[1000000], cnt[1000001], result[1000000];
stack<pair<int, int>> st;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> num_sequence;
    for(int i = 0; i < num_sequence; i++){
        cin >> input[i];
        // 해당 숫자의 출현 빈도 체크
        cnt[input[i]]++;
    }

    st.emplace(input[0], 0);
    for(int i = 1; i < num_sequence; i++){
        while(!st.empty() && cnt[st.top().first] < cnt[input[i]]){
            result[st.top().second] = input[i];
            st.pop();
        }
        st.emplace(input[i], i);
    }
    while(!st.empty()){
        result[st.top().second] = -1;
        st.pop();
    }

    for(int i = 0; i < num_sequence; i++) cout << result[i] << " ";
    return 0;
}

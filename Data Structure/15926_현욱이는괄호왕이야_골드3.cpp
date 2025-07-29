// 열린괄호가 들어올 때
// 닫힌 괄호가 들어올 때
// -> 올바른 괄호 문자열일 시 or 올바르지 않은 괄호 문자열일 시

#include <bits/stdc++.h>
using namespace std;

int result[200000];

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int len_input;

    cin >> len_input;

    stack<pair<char, int>> st;

    for(int i = 0; i < len_input; i++){
        char temp;
        cin >> temp;

        if(temp == '('){
            st.emplace('(', i);
        }
        else{
            if(!st.empty() && st.top().first == '('){
                int start = st.top().second; st.pop();
                if(result[start - 1]) result[i] = result[start - 1] + i - start + 1;
                else result[i] = i - start + 1;
            }
            else{
                while(!st.empty()) st.pop();
            }
        }
    }

    cout << *max_element(result, result + len_input);
    return 0;
}

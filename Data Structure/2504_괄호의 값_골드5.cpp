// (()[[]])([]) = (()) ([[]]) ([])
// 괄호가 처음으로 끝날 때 더함. 연속적으로 끝나면(감싸져있다는 뜻) 더하지 않음

#include <bits/stdc++.h>
using namespace std;

void fail(){
    cout << 0;
    exit(0);
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    string input;
    cin >> input;
    int result = 0;
    int temp = 1;
    bool before = false;
    stack<char> st;
    for(char i : input){
        if(i == '('){
            temp *= 2;
            st.push('(');
            before = false;
        }
        else if(i == ')'){
            if(!st.empty() && st.top() == '('){
                if(!before) result += temp;
                temp /= 2;
                st.pop();
                before = true;
            }
            else fail();
        }
        else if(i == '['){
            temp *= 3;
            st.push('[');
            before = false;
        }
        else{
            if(!st.empty() && st.top() == '['){
                if(!before) result += temp;
                temp /= 3;
                st.pop();
                before = true;
            }
            else fail();
        }
    }

    if(!st.empty()) fail();
    cout << result;
    return 0;
}


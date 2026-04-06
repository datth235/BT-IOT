#include<bits/stdc++.h>

using namespace std;

int priority(char op){
    if(op == '-' || op == '+') return 1;
    if(op == '/' || op == '*') return 2;
    return 0;
}

string infix_to_postfix(string s){
    stack<char> st;
    string output="";

    for(char c : s){

        if(isdigit(c)){
            output += c;
            output += ' ';
        }

        else if(c=='('){
            st.push(c);
        }

        else if(c==')'){
            while(st.top()!='('){
                output += st.top();
                output += ' ';
                st.pop();
            }
            st.pop();
        }

        else if(c=='+' || c=='-' || c=='*' || c=='/'){
            while(!st.empty() && priority(st.top()) >= priority(c)){ // 2 + 3 * 4 -> độ ưu tiên cao hơn thì ra trước
                output += st.top();
                output += ' ';
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()){
        output += st.top();
        output += ' ';
        st.pop();
    }

    return output;
}

int to_int(string s){
    int ret = 0;
    for(char c : s){
        ret = ret * 10 + (c - '0');
    }
    return ret;
}

int expr(string s){
    stringstream ss(s);
    string token;

    stack<int> st;
    int tmp = 0;

    while(ss >> token){
        if(token != "+" && token != "-" && token != "/" && token != "*"){
            tmp = to_int(token);
            st.push(tmp);
        }
        else{
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();

            if(token == "+") st.push(a + b);
            if(token == "-") st.push(a - b);
            if(token == "*") st.push(a * b);
            if(token == "/") st.push(a / b);
        }
    }

    return st.top();
}

int main(){
    string s;
    getline(cin, s);
    cout << expr(s) << endl;
    return 0;
}
/*
INPUT: (2 + 3) * (4 - 1)
OUTPUT: 2 3 + 4 1 - *  
*/
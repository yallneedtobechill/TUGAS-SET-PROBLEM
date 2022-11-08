#include <iostream>
#include <stack>
#include "nomer3.hpp"

using namespace std;

int main(){
    string expression = "3+((5+9)*2)";
    string postfix = convertInfixToPostfix(expression);

    Node *x, *y, *z;
    Tree t;
    Stack s;

    for (int i = 0; i < postfix.length(); i++){
        if (postfix[i] == ' '){
            continue;
        }

        if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/'){
            z = new Node(postfix[i]);
            x = s.pop();
            y = s.pop();
            z->left = y;
            z->right = x;
            s.push(z);
        }else{
            z = new Node(postfix[i]);
            s.push(z);
        }
        
        
    }
    t.inOrder(z);
    return 0;
}


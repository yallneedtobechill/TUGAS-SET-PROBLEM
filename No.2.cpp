#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isMathOperator(char equ) {
// cek operasi matematika
    switch (equ) {
        case '+': 
        case '-': 
        case '*': 
        case '/': 
            return true;
            break;
        default:
            return false;
            break;
    }
}

int orderOfOperations(char equ) {
// equation
    int priority = 0;
    switch (equ) {
        case '*': 
        case '/': 
            priority = 2;
            break;
        case '-': 
        case '+':
            priority = 1;
            break;
    }
    return priority;
}

string convertInfixToPostfix(string infix) {
    string postfix;
    stack<char> charStack;
 
    for (int x = 0; x < infix.length(); x++) {
        if (isdigit(infix[x])) { 
            if (postfix.length() > 0 && !isdigit(postfix.back())) { 
                //karakter postfix paling belakang bukan angka
                if (!isspace(postfix.back())) { 
                    postfix += " ";//karakter postfix paling belakang bukan spasi, terus ditambah spasi
                }
            }
            postfix += infix[x]; // misal postfix.back() nya bukan suatu digit, langsung push ke string
        }else if (isMathOperator(infix[x])) {  //Dicek apakah ekspresinya berupa math operator
            if (postfix.length() > 0 && !isspace(postfix.back())) { 
                postfix += " ";//Apabila setelah operator tidak ada spasi, akan diberi spasi
            }
            // while berfungsi sebagai pengecekan apabila stacknya tidak kosong
            // math ops akan ada di atas stack, apakah lebih besar sama dengan dari
            // math ops pada tranversing sekarang
            while ((!charStack.empty()) && (orderOfOperations(charStack.top()) >= orderOfOperations(infix[x]))) {
                // Kalau lebih  besar maka math ops akan dipush ke string postfix
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Apabila setelah operator tidak ada spasi, akan diberikan spasi
                    postfix += " ";
                }
                postfix += charStack.top();
                charStack.pop();
            }
            //Pop, setelah itu push sisa operator yang belum ke stack
            charStack.push(infix[x]);
        }else if (infix[x] == '(') { //Tanda "(" akan dipush ke stack
            charStack.push(infix[x]);
 
        }else if (infix[x] == ')') { 
            while ((!charStack.empty()) && (charStack.top() != '(')) {
                //Apabila ada ")"  maka akan diulangi dengan while, yang akan  mengecek dan akan push stack yang bukan tanda ")"
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Apabila setelah operator tidak ada spasi, akan diberikan spasi
                    postfix += " ";
                }
                
                postfix += charStack.top(); //Operator yang ada sebelum tanda "(" akan di push
                charStack.pop();
            }
 
            if (!charStack.empty()) {
                charStack.pop();
            } else {
                throw invalid_argument {
                    "PARENTHESIS SALAH"
                };
            }
            //Apabila tidak ketemu tanda "("
        } else {
            throw invalid_argument {
                "INVALID INPUT"
            };
        }
    }
 
    while (!charStack.empty()) {
        if (postfix.length() > 0 && !isspace(postfix.back())) { //Apabila setelah operator tidak ada spasi, akan diberikan spasi
            postfix += " ";
        }
        postfix += charStack.top(); 
        charStack.pop();
    }
    return postfix;
}

int evaluate(string postfix){
    stack<int> ns;
    for (int i = 0; i < postfix.length(); i++){
        char c = postfix[i];
        if (c == ' '){ 
            continue; 
        }else if(isdigit(c)){
            int n = 0;
            while (isdigit(c)){
                n = n * 10 + (int)(c - '0'); 
                // Angka yang lebih depan akan dikali 10 dan dilanjutkan dengan menambah angka selanjutnya dan diulangi
                // EX 153, nanti 
                // (1)=> n = 0 * 10 + 1
                //              n = 1
                // (2)=> n = 1 * 10 + 5
                //                 n = 15
                // (3)=> n = 15 * 10 + 3
                //                 n = 153

                i++;
                c = postfix[i];
            }
            i--; 
            ns.push(n);
            
        }else{
            int val1 = ns.top(); ns.pop();
            int val2 = ns.top(); ns.pop();
            switch (c){
            case '+':
                ns.push(val2 + val1);
                break;
            case '-':
                ns.push(val2 - val1);
                break;
            case '*':
                ns.push(val2 * val1);
                break;
            case '/':
                ns.push(val2 / val1);
                break;
            default:
                throw invalid_argument{
                    "INVALID OPERATOR"
                };
                break;
            }
        }
    }
    return ns.top();
}


int main(){
    string number;
    cin >> number;
    string postfix = convertInfixToPostfix(number);
    cout << evaluate(postfix);
    
    return 0;
}
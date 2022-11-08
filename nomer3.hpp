#ifndef nomer3_hpp
#define nomer3_hpp

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Tree {
    public:
    void inOrder(Node *n){
        if (n == NULL){
            return;
        }else{
            inOrder(n->left);
            cout << n->nilai << " ";
            inOrder(n->right);
        }
    }
};

class Node {
    public:
        char nilai;
        Node *left;
        Node *right;
        Node *next = NULL;
    
        Node (char c){
            this->nilai = c;
            left = NULL;
            right = NULL;
        }

        Node(){
            left = NULL;
            right = NULL;
        }

    friend class Tree;
    friend class Stack;
};

class Stack {
    Node *head = NULL;
    public:
        void push(Node*);
        Node* pop();
        friend class Tree;
};


void Stack::push(Node* e){
    if (head == NULL){
        head = e;
    }else{
        e->next = head;
        head = e;
    }
}

Node* Stack::pop(){
    Node* p = head;
    head = head->next;
    return p;
}

bool isMathOperator(char equ) {
// cek kalo dia math ooperator atau bukan
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
// Order operasi
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
                    postfix += " "; //karakter postfix paling belakang bukan spasi, terus ditambah spasi
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
                //Kalau lebih  besar maka math ops akan dipush ke string postfix
                if (postfix.length() > 0 && !isspace(postfix.back())) { //Apabila setelah operator tidak ada spasi, akan diberikan spasi
                    postfix += " ";
                }
                postfix += charStack.top();
                charStack.pop();
            }
            // push sisa operator yang belum ke stack
            charStack.push(infix[x]);
        }else if (infix[x] == '(') { //Tanda "(" akan dipush ke stack
            charStack.push(infix[x]);
 
        }else if (infix[x] == ')') {
            //Apabila ada ")"  maka akan diulangi dengan while, yang akan  mengecek dan akan push stack yang bukan tanda ")"
            while ((!charStack.empty()) && (charStack.top() != '(')) {
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
        } else {
            throw invalid_argument {
                "INVALID INPUT"
            };
        }
    }
 
    //Masukin sisanya ke string postfix
    while (!charStack.empty()) {
        if (postfix.length() > 0 && !isspace(postfix.back())) { //Apabila setelah operator tidak ada spasi, akan diberikan spasi
            postfix += " ";
        }
        postfix += charStack.top(); 
        charStack.pop(); 
    }
    return postfix;
}

#endif
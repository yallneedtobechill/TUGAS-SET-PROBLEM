#include<iostream>
#include<stack>
using namespace std;
bool isBalanced(string input) {
   stack<char> s;
   char eq;
   for (int i=0; i<input.length(); i++) {    //cek kondisi pada setiap karakter yang ada
      if (input[i]=='('||input[i]=='['||input[i]=='{') {    //jika input nya adalah "[", "(", "{" maka push
         s.push(input[i]);
         continue;
      }
      if (s.empty())    //harus ada "]", "}", ")" karena stack tidak boleh kosong 
         return false;
         switch (input[i]) {
            case ')':    //pop dan periksa tanda kurung ")"
               eq= s.top();
               s.pop();
               if (eq=='{' || eq=='[')
                  return false;
                  break;
            case '}': //pop dan periksa tanda kurung "}"
               eq= s.top();
               s.pop();
               if (eq=='(' || eq=='[')
                  return false;
                  break;
            case ']': //pop dan periksa tanda kurung "]"
               eq= s.top();
               s.pop();
               if (eq=='(' || eq== '{')
                  return false;
                  break;
         }
      }
      return (s.empty()); //pada saat stack = empty, return true
}
main() {
   string input = "[{}(){()}]";
   if (isBalanced(input))
      cout << "Balanced";
   else
      cout << "Not Balanced";
}
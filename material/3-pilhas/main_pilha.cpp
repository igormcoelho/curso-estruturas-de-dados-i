
#include<stack>
#include<iostream>

int main()
{

   std::stack<char> p;
   p.push('A');
   p.push('B');
   printf("%c\n", p.top()); // B
   p.pop();
   printf("%c\n", p.top()); // A


   return 0;
}

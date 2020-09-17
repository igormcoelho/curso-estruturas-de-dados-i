
#include<stack>
#include<iostream>

int main()
{

   std::stack<char> p;
   p.push('A');
   p.push('B');
   printf("%c\n", p.top());
   p.pop();
   printf("%c\n", p.top());


   return 0;
}


#include<queue>
#include<iostream>

int main()
{

   std::queue<char> p;
   p.push('A');
   p.push('B');
   printf("%c\n", p.front()); // A
   p.pop();
   printf("%c\n", p.front()); // B


   return 0;
}


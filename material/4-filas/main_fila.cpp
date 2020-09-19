
#include<queue>
#include<iostream>

int main()
{

   std::queue<char> p;
   p.push('A');
   p.push('B');
   printf("%c\n", p.front());
   p.pop();
   printf("%c\n", p.front());


   return 0;
}


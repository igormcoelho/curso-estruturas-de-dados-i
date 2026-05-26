#include <fmt/core.h>

#include <stack>
#include <string>
using fmt::print;

std::string rev(std::string s) {
  if (s.length() <= 1) return s;
  std::string r = rev(s.substr(1)) + s[0];
  return r;
}

std::string revs(std::string s) {
  std::stack<char> pchars;
  for (char c : s) pchars.push(c);
  std::string r;
  // reconstroi string ao contrário
  while (pchars.size() > 0) {
    r += pchars.top();
    pchars.pop();
  }
  return r;
}

int main() {
  print("{}\n", rev("ESCOLA"));
  print("{}\n", revs("ESCOLA"));
  std::string s = "ESCOLA";
  print("{}\n", s.substr(2));
  return 0;
}
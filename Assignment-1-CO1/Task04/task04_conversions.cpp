#include <iostream>
int main() {
 int a=7,b=2; double c=a/b; double d=static_cast<double>(a)/b;
 std::cout << c << ' ' << d << '\n';
 char ch=static_cast<char>('A'+2);
 std::cout << ch << ' ' << static_cast<int>(ch)+1 << '\n';
 bool flag=static_cast<bool>(5);
 std::cout << flag << ' ' << std::boolalpha << flag << '\n';
 unsigned int u=1; int s=-1;
 std::cout << (s<u ? "s < u" : "s >= u") << '\n';
 int safe{3}; std::cout << safe << '\n';
 // int narrowing{3.7}; // Uncomment to see compile-time narrowing error.
}

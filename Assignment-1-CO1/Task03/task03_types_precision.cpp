#include <climits>
#include <iomanip>
#include <iostream>
int main() {
 std::cout << "sizeof(bool)=" << sizeof(bool) << " sizeof(char)=" << sizeof(char)
 << " sizeof(int)=" << sizeof(int) << " sizeof(long long)=" << sizeof(long long)
 << " sizeof(float)=" << sizeof(float) << " sizeof(double)=" << sizeof(double) << '\n';
 std::cout << "INT_MAX=" << INT_MAX << " LLONG_MAX=" << LLONG_MAX << '\n';
 long long exactPaise=0; double rupees=0.0;
 for(int i=0;i<5;++i){ exactPaise+=1001; rupees+=10.01; }
 std::cout << std::fixed << std::setprecision(10)
 << "Integer total=" << exactPaise << " paise; double total=Rs " << rupees << '\n';
 std::cout << "0.1*10 as double=" << 0.1*10.0 << '\n';
}

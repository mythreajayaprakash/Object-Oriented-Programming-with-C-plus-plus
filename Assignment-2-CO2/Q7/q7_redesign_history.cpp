#include <array>
#include <chrono>
#include <iostream>
#include <cstddef>
class ShiftHistory{static constexpr std::size_t C=50;std::array<int,C>a{};std::size_t n=0;
public:void add(int v){if(n<C)a[n++]=v;else{for(std::size_t i=1;i<C;++i)a[i-1]=a[i];a[C-1]=v;}}int newest()const{return n?a[n-1]:0;}};
class CircularHistory{static constexpr std::size_t C=50;std::array<int,C>a{};std::size_t n=0,next=0;
public:void add(int v){a[next]=v;next=(next+1)%C;if(n<C)++n;}int newest()const{return n?a[(next+C-1)%C]:0;}};
int main(){constexpr int N=200000;ShiftHistory s;CircularHistory c;
 auto a=std::chrono::steady_clock::now();for(int i=0;i<N;++i)s.add(i);auto b=std::chrono::steady_clock::now();
 auto d=std::chrono::steady_clock::now();for(int i=0;i<N;++i)c.add(i);auto e=std::chrono::steady_clock::now();
 auto x=std::chrono::duration_cast<std::chrono::nanoseconds>(b-a).count();
 auto y=std::chrono::duration_cast<std::chrono::nanoseconds>(e-d).count();
 std::cout<<"Shift newest="<<s.newest()<<" elapsed_ns="<<x<<'\\n';
 std::cout<<"Circular newest="<<c.newest()<<" elapsed_ns="<<y<<'\\n';
 std::cout<<"Both retain 50 records; repeat runs and record actual measurements.\\n";
 return s.newest()==c.newest()?0:1;
}

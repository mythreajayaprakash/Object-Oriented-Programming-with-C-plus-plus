#include <chrono>
#include <iostream>
class Time{int h,m;public:Time(int hh,int mm):h(hh),m(mm){}
 friend int minutesBetween(const Time&,const Time&);
 friend bool earlier(const Time&,const Time&);};
inline int minutesBetween(const Time&a,const Time&b){int x=a.h*60+a.m,y=b.h*60+b.m;return x>y?x-y:y-x;}
inline bool earlier(const Time&a,const Time&b){return a.h*60+a.m<b.h*60+b.m;}
int main(){
 Time departure(9,45),arrival(13,10);
 std::cout<<minutesBetween(departure,arrival)<<' '<<std::boolalpha<<earlier(arrival,departure)<<'\\n';
 Time same1(12,0),same2(12,0),before(11,55),after(12,5);
 std::cout<<minutesBetween(same1,same2)<<' '<<earlier(same1,same2)<<'\\n';
 std::cout<<minutesBetween(before,after)<<' '<<earlier(before,after)<<'\\n';
 constexpr int N=10000000;volatile long long sum=0;
 auto start=std::chrono::steady_clock::now();
 for(int i=0;i<N;++i){sum+=minutesBetween(departure,arrival);sum+=earlier(departure,arrival)?1:0;}
 auto stop=std::chrono::steady_clock::now();
 std::cout<<"Iterations "<<N<<" elapsed_ns "
 <<std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count()
 <<" checksum "<<sum<<'\\n';
}

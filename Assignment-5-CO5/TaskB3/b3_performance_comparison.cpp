#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdlib>

struct BillData { int type; double a,b; int days; };
double switchTotal(const BillData& x) {
    switch(x.type) {
        case 0: return x.a+x.b;
        case 1: return x.days*x.a+x.b;
        case 2: return x.a;
        default: return x.a+x.b;
    }
}
struct Base { virtual ~Base()=default; virtual double total()const=0; };
struct OP : Base { double a,b; OP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct IP : Base { int d;double r,s;IP(int x,double y,double z):d(x),r(y),s(z){}double total()const override{return d*r+s;} };
struct DC : Base { double p;explicit DC(double x):p(x){}double total()const override{return p;} };

template<class F> long long timeNs(F f) {
    auto a=std::chrono::steady_clock::now(); volatile double sum=f();
    auto b=std::chrono::steady_clock::now(); (void)sum;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(b-a).count();
}
int main(int argc,char**argv) {
    const int n = argc>1 ? std::atoi(argv[1]) : 1000000;
    std::vector<BillData> tagged; std::vector<Base*> poly;
    tagged.reserve(n); poly.reserve(n);
    std::vector<OP> ops; ops.reserve(n/3+1);
    std::vector<IP> ips; ips.reserve(n/3+1);
    std::vector<DC> dcs; dcs.reserve(n/3+1);
    for(int i=0;i<n;++i) {
        int t=i%3;
        if(t==0){tagged.push_back({0,500,1200,0});ops.emplace_back(500,1200);}
        else if(t==1){tagged.push_back({1,2500,40000,3});ips.emplace_back(3,2500,40000);}
        else {tagged.push_back({2,18000,0,0});dcs.emplace_back(18000);}
    }
    // Pointer list is populated after stable vectors have finished growing.
    std::size_t oi=0,ii=0,di=0;
    for(int i=0;i<n;++i) {
        if(i%3==0)poly.push_back(&ops[oi++]);
        else if(i%3==1)poly.push_back(&ips[ii++]);
        else poly.push_back(&dcs[di++]);
    }
    auto switchTime=timeNs([&](){double s=0;for(const auto&x:tagged)s+=switchTotal(x);return s;});
    auto virtualTime=timeNs([&](){double s=0;for(const Base*x:poly)s+=x->total();return s;});
    std::cout<<"n="<<n<<" switch_ns="<<switchTime<<" virtual_ns="<<virtualTime<<'\n';
    std::cout<<"Repeat at n=1000, 1000000 and 10000000 with -O2; compare totals as well as times.\n";
}

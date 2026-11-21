#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

bool returnValidate(double x) { return x >= 0; }
void exceptionValidate(double x) { if(x<0) throw std::invalid_argument("negative"); }

template<class F> long long measure(F f) {
    auto a=std::chrono::steady_clock::now(); f();
    auto b=std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count();
}
int main() {
    constexpr int N=1000000;
    for(int invalidPercent:{0,1,50}) {
        std::vector<double> data(N,100.0);
        const int bad=N*invalidPercent/100;
        for(int i=0;i<bad;++i)data[i]=-1;
        volatile int errors=0;
        auto rc=measure([&](){for(double x:data)if(!returnValidate(x))++errors;});
        auto ex=measure([&](){for(double x:data){try{exceptionValidate(x);}catch(const std::exception&){++errors;}}});
        std::cout<<invalidPercent<<"% invalid: return_code_ms="<<rc
                 <<" exception_ms="<<ex<<" errors_seen="<<errors<<'\n';
    }
    std::cout<<"Repeat runs; these timings depend on hardware, compiler and system load.\n";
}

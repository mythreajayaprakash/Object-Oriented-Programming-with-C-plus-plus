#include <iostream>
#include <iomanip>
#include <limits>
int main(){
 const long long farePaise=1200, counts[]={20000,500000,3000000};
 for(long long n:counts){long long exact=n*farePaise;double rupees=n*(static_cast<double>(farePaise)/100.0);
 std::cout<<n<<" journeys: "<<exact<<" paise; double Rs "<<std::fixed<<std::setprecision(2)<<rupees
 <<"; fits int="<<std::boolalpha<<(exact<=std::numeric_limits<int>::max())<<'\n';}
 std::cout<<"INT_MAX="<<std::numeric_limits<int>::max()<<" LLONG_MAX="<<std::numeric_limits<long long>::max()<<'\n';
}

#include <array>
#include <iostream>
#include <set>
#include <stdexcept>
enum class Zone{Inner,Middle,Outer,Airport};
constexpr std::array<long long,4> FARES={1000,2000,3000,6000};
class MonthlyPass{
 std::set<Zone> zones_;
public:
 MonthlyPass(Zone a,Zone b){if(a==b)throw std::invalid_argument("Choose two different zones");zones_.insert(a);zones_.insert(b);}
 bool covers(Zone z)const{return zones_.count(z)>0;}
};
class SmartCard{
 long long balance_;
public:
 explicit SmartCard(long long b):balance_(b){}
 bool deduct(long long f){if(f<0||balance_-f<5000)return false;balance_-=f;return true;}
 long long balance()const{return balance_;}
};
long long calculate(Zone z,bool peak,bool weekend,const MonthlyPass* pass){
 if(pass&&pass->covers(z))return 0;
 auto i=static_cast<std::size_t>(z);if(i>=FARES.size())return -1;
 long long f=FARES[i];
 if(weekend)f-=f*10/100;else if(peak)f+=f*20/100;
 return f;
}
int main(){
 SmartCard card(20000);MonthlyPass pass(Zone::Inner,Zone::Middle);
 struct Trip{Zone z;bool peak,weekend,usePass;};
 Trip trips[]={{Zone::Airport,true,false,false},{Zone::Outer,true,true,false},{Zone::Inner,false,false,true},{Zone::Middle,true,false,true}};
 for(const auto&t:trips){long long f=calculate(t.z,t.peak,t.weekend,t.usePass?&pass:nullptr);
 if(f<0)std::cout<<"Invalid zone\n";else if(f==0)std::cout<<"Covered by pass; balance "<<card.balance()<<" paise\n";
 else if(card.deduct(f))std::cout<<"Fare "<<f<<" paise; balance "<<card.balance()<<" paise\n";
 else std::cout<<"Denied: minimum Rs 50 must remain\n";}
}

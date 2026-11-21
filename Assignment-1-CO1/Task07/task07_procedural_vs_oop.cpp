#include <iostream>
constexpr long long MIN_BALANCE=5000;
bool canTravelProcedural(long long b,long long f){return f>=0&&b-f>=MIN_BALANCE;}
bool deductProcedural(long long& b,long long f){if(!canTravelProcedural(b,f))return false;b-=f;return true;}
class SmartCard{
 long long balance_;
public:
 explicit SmartCard(long long b):balance_(b){}
 bool canTravel(long long f)const{return f>=0&&balance_-f>=MIN_BALANCE;}
 bool deduct(long long f){if(!canTravel(f))return false;balance_-=f;return true;}
 long long balance()const{return balance_;}
};
int main(){
 long long balance=10000;
 std::cout<<"Procedural accepted="<<deductProcedural(balance,2000)<<" balance="<<balance<<'\n';
 SmartCard card(10000);
 std::cout<<"OOP accepted="<<card.deduct(2000)<<" balance="<<card.balance()<<'\n';
}

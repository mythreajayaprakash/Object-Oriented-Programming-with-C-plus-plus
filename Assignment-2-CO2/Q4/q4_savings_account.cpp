#include <array>
#include <iostream>
#include <cstddef>
class SavingsAccount{
 static constexpr std::size_t CAP=10;
 long long accountNumber,balancePaise;
 std::array<long long,CAP> history{};
 std::size_t count=0,next=0;
 void record(long long amount){history[next]=amount;next=(next+1)%CAP;if(count<CAP)++count;}
public:
 SavingsAccount(long long no,long long opening):accountNumber(no),balancePaise(opening){}
 void deposit(long long p){if(p<=0){std::cout<<"Invalid deposit\\n";return;}balancePaise+=p;record(p);}
 bool withdraw(long long p){if(p<=0||p>balancePaise){std::cout<<"Withdrawal rejected\\n";return false;}balancePaise-=p;record(-p);return true;}
 void miniStatement()const;
};
void SavingsAccount::miniStatement()const{
 std::cout<<"Account: "<<accountNumber<<"\\nTransactions oldest first:\\n";
 std::size_t start=count==CAP?next:0;
 for(std::size_t i=0;i<count;++i)std::cout<<history[(start+i)%CAP]<<" paise\\n";
 std::cout<<"Balance: "<<balancePaise<<" paise\\n";
}
int main(){SavingsAccount a(192424089,500000);a.deposit(10000);a.withdraw(2500);
 for(int i=1;i<=10;++i)a.deposit(i*100);a.miniStatement();}

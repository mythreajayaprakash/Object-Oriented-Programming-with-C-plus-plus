#include <iomanip>
#include <iostream>
#include <limits>
long long readNumber(const char* prompt){
 long long v{}; while(true){std::cout<<prompt;if(std::cin>>v)return v;
 std::cout<<"Invalid integer; try again.\n";std::cin.clear();
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');}
}
int main(){
 long long balance=readNumber("Balance in paise: "),fare=readNumber("Fare in paise: ");
 if(balance<0||fare<0){std::cout<<"Negative values are invalid.\n";return 1;}
 if(balance-fare>=5000)std::cout<<"Accepted. Remaining Rs "<<std::fixed<<std::setprecision(2)<<(balance-fare)/100.0<<'\n';
 else std::cout<<"Denied: Rs 50 must remain.\n";
}

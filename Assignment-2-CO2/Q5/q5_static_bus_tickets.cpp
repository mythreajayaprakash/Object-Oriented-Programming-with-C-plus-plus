#include <iostream>
#include <string>
class BusTicket{
 static int issued;static const int CAPACITY=3;int seat;std::string name;
public:
 explicit BusTicket(const std::string& n):seat(0),name(n){if(issued<CAPACITY){++issued;seat=issued;}}
 static int count(){return issued;}
 void print()const{std::cout<<name<<": "<<(seat?"Seat "+std::to_string(seat):std::string("Waiting"))<<'\\n';}
};
int BusTicket::issued=0;
class Token{static int next;int id;public:Token():id(++next){}int get()const{return id;}static int issued(){return next-100;}};
int Token::next=100;
void createInFunction(){BusTicket e("Esha"),f("Farhan");e.print();f.print();}
int main(){
 Token counter[3];Token extra;
 std::cout<<counter[0].get()<<' '<<counter[2].get()<<' '<<extra.get()<<' '<<Token::issued()<<'\\n';
 BusTicket trip[4]={BusTicket("Asha"),BusTicket("Bala"),BusTicket("Chitra"),BusTicket("Dev")};
 for(const auto&t:trip)t.print();std::cout<<"Issued: "<<BusTicket::count()<<'\\n';
 createInFunction();std::cout<<"Issued after function: "<<BusTicket::count()<<'\\n';
}

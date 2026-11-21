#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class Bill { public: virtual ~Bill()=default; virtual double total()const=0; virtual std::string type()const=0; };
class OPBill:public Bill { double c,t; public:OPBill(double a,double b):c(a),t(b){}double total()const override{return c+t;}std::string type()const override{return "OP";} };
class InPatientBill:public Bill { int d;double r,s;public:InPatientBill(int x,double y,double z):d(x),r(y),s(z){}double total()const override{return d*r+s;}std::string type()const override{return "IP";} };
class MaternityBill:public Bill { double package;public:explicit MaternityBill(double p):package(p){}double total()const override{return package;}std::string type()const override{return "Maternity";} };

class Payer { public:virtual ~Payer()=default;virtual double covered(const Bill&)const=0; };
class SelfPay:public Payer { public:double covered(const Bill&b)const override{return b.total();} };
class CorporateTieUp:public Payer { double percent;public:explicit CorporateTieUp(double p):percent(p){}double covered(const Bill&b)const override{return b.total()*percent/100.0;} };

int main(){
 std::vector<std::unique_ptr<Bill>> bills;
 bills.push_back(std::make_unique<OPBill>(500,1200));
 bills.push_back(std::make_unique<InPatientBill>(3,2500,40000));
 bills.push_back(std::make_unique<MaternityBill>(65000));
 SelfPay patient;CorporateTieUp corporate(70);
 for(const auto&b:bills)
   std::cout<<b->type()<<" total="<<b->total()
            <<" patient="<<patient.covered(*b)
            <<" corporate="<<corporate.covered(*b)<<'\n';
}

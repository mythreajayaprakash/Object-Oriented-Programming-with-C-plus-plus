#include <iostream>
struct Parcel{double kg;bool express;bool insured;};
double compute(double kg,bool express,bool insured){double c=kg*40.0;if(express)c+=50;if(insured)c+=25;return c;}
double charge(double kg,bool express=false,bool insured=false){return compute(kg,express,insured);}
double charge(int grams){return compute(static_cast<double>(grams)/1000.0,false,false);}
double charge(const Parcel& p){return compute(p.kg,p.express,p.insured);}
int main(){Parcel p{2.5,true,true};
 std::cout<<"charge(2) [int grams] = "<<charge(2)<<'\\n';
 std::cout<<"charge(2.0) [double kg] = "<<charge(2.0)<<'\\n';
 std::cout<<"charge(2.0f) [float promotes to double] = "<<charge(2.0f)<<'\\n';
 std::cout<<"charge(2000) [int grams] = "<<charge(2000)<<'\\n';
 std::cout<<"charge(2.0,true) = "<<charge(2.0,true)<<'\\n';
 std::cout<<"charge(Parcel) = "<<charge(p)<<'\\n';
}

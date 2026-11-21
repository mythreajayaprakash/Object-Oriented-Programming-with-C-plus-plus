#include <iostream>
enum class Zone{Inner,Middle,Outer};
long long base(Zone z){switch(z){case Zone::Inner:return 1000;case Zone::Middle:return 2000;case Zone::Outer:return 3000;}return -1;}
bool peak(int h){return (h>=8&&h<10)||(h>=17&&h<20);}
long long fare(Zone z,int h){if(h<0||h>23)return -1;long long f=base(z);if(f<0)return -1;if(peak(h))f+=f*20/100;return f;}
bool allowed(long long b,long long f){return f>=0&&b-f>=5000;}
int main(){
 struct T{const char* name;Zone z;int h;long long b,expected;bool ok;};
 T tests[]={{"Inner off peak",Zone::Inner,7,10000,1000,true},{"08:00 peak",Zone::Inner,8,10000,1200,true},
 {"10:00 off peak",Zone::Inner,10,10000,1000,true},{"17:00 peak",Zone::Middle,17,10000,2400,true},
 {"20:00 off peak",Zone::Outer,20,10000,3000,true},{"exact Rs50 remaining",Zone::Outer,8,8600,3600,true},
 {"below Rs50",Zone::Outer,8,8500,3600,false}};
 int passed=0;for(const auto&t:tests){long long f=fare(t.z,t.h);bool ok=f==t.expected&&allowed(t.b,f)==t.ok;
 std::cout<<(ok?"PASS ":"FAIL ")<<t.name<<" fare="<<f<<" accepted="<<std::boolalpha<<allowed(t.b,f)<<'\n';if(ok)++passed;}
 std::cout<<"Passed "<<passed<<"/"<<(sizeof(tests)/sizeof(tests[0]))<<" tests\n";
 std::cout<<"Example five-journey total = "<<1000+2400+2000+3600+3000<<" paise\n";
 return passed==(sizeof(tests)/sizeof(tests[0]))?0:1;
}

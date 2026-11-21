#include <iostream>
bool peak(int h){return (h>=8 && h<10)||(h>=17 && h<20);}
int main(){
 int x=5,y=3; std::cout<<x+y*2<<' '<<(x+y)*2<<'\n';
 int z=x++ + ++y; std::cout<<z<<' '<<x<<' '<<y<<'\n';
 std::cout<<(x>y?x:y)<<' '<<x%4*2<<'\n';
 std::cout<<10/3<<' '<<10%3<<' '<<-10/3<<' '<<-10%3<<'\n';
 int k=0; for(int i=0;i<10;i+=3) k+=i; std::cout<<k<<'\n';
 std::cout<<std::boolalpha<<peak(8)<<' '<<peak(10)<<' '<<peak(17)<<' '<<peak(20)<<'\n';
}

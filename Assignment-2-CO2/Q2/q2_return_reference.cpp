#include <iostream>
#include <vector>
int& highestMark(int a[],int n){int best=0;for(int i=1;i<n;++i)if(a[i]>a[best])best=i;return a[best];}
const int& highestMarkReadOnly(const int a[],int n){int best=0;for(int i=1;i<n;++i)if(a[i]>a[best])best=i;return a[best];}
int highestMarkCopy(const int a[],int n){int best=0;for(int i=1;i<n;++i)if(a[i]>a[best])best=i;return a[best];}
// Unsafe example intentionally disabled: returning a reference to a local variable dangles.
// int& bad(){int local=42;return local;}
int main(){
 int marks[]={78,91,84,88,95};highestMark(marks,5)+=2;
 std::cout<<"Modified highest mark: "<<highestMarkCopy(marks,5)<<'\\n';
 std::cout<<"Read-only highest mark: "<<highestMarkReadOnly(marks,5)<<'\\n';
 std::vector<int> v={70,80,90};int* old=&v[2];std::cout<<"Before growth: "<<*old<<'\\n';
 v.reserve(100);std::cout<<"After reserve, access by fresh index: "<<v[2]<<'\\n';
 // Do not dereference old: vector reallocation may invalidate it.
}

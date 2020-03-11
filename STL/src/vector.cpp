#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> vec;
    for(int i=0;i<=5;i++){
	vec.push_back(i);
    }
    cout<<"vector contains: ";
    for(vector<int>::iterator it = vec.begin();it!=vec.end();++it){
	cout<<' '<<*it;
    }
    cout<<endl;
    return 0;
}

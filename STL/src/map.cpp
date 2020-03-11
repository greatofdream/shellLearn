#include <iostream>
#include <map>
using namespace std;
int main(){
	map<char,int> m;
	m['z']=100;
	m['a']=1000;
	m['q']=10;
	for(map<char,int>::iterator it=m.begin();it!=m.end();++it){
		cout<<it->first<<":"<<it->second<<endl;
	}
	return 0;
}

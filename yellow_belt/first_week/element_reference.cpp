#include <map>
#include <string>
#include <iostream>

using namespace std;

template <typename K_t, typename V_t> 
V_t& GetRefStrict(map<K_t, V_t>& mp, const K_t& key);

template <typename K_t, typename V_t>
V_t& GetRefStrict(map<K_t, V_t>& mp, const K_t& key){
	try{
		return mp.at(key);
	}
	catch (out_of_range& ex){
		throw runtime_error("out_of_range");
	}
}

int main(){
	map<double, double> m = { { 1.3, 3.3 } };
	double& item = GetRefStrict(m, 1.3);
	item = 12;
	cout << m[1.3] << endl;

	system("pause");
}

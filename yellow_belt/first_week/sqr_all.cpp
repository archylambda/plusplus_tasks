#include <vector>
#include <iostream>
#include <map>
#include <utility>
//#include "template_print.h"

using namespace std;

template <typename First, typename Second>
map<First, Second> Sqr(const map<First, Second>& mp);
template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& pr);
template <typename T>
vector<T> Sqr(const vector<T>& vec);
template <typename T>
T Sqr(const T& item);

template <typename T>
T Sqr(const T& item){
	return item*item;
}

template <typename First, typename Second>
map<First, Second> Sqr(const map<First, Second>& mp){
	map<First, Second> res = mp;
	for (auto& item : res){
		item.second = Sqr(item.second);
	}
	return res;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& pr){
	pair<First, Second> res = pr;
	res.first = Sqr(res.first);
	res.second = Sqr(res.second);

	return res;
}

template <typename T>
vector<T> Sqr(const vector<T>& vec){
	vector<T> res = vec;
	for (T& item: res){
		item = Sqr(item);
	}

	return res;
}

//int main(){
//	// Пример вызова функции
//	vector<int> v = { 1, 2, 3 };
//	cout << "vector:";
//	for (int x : Sqr(v)) {
//		cout << ' ' << x;
//	}
//	cout << endl;
//
//	map<int, vector<pair<int, int>>> map_of_pairs = {
//		{ 4, { { 2, 2 }, {3, 3} } },
//		{ 7, {{ 4, 3 }, { 4, 4 } } }
//	};
//	cout << "map of pairs:" << endl;
//	for (const auto& x : Sqr(map_of_pairs)) {
//		cout << x;
//	}
//
//	system("pause");
//	return 0;
//}
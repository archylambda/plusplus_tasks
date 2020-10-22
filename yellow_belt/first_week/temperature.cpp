#include <vector>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <algorithm>
#include <limits>
#include <list>

int main(){


	int n;
	std::cin >> n;
	
	std::vector<int> temperature(n);
	int64_t sum = 0;

	for (int i = 0; i < n; ++i){
		std::cin >> temperature[i];
		sum += temperature[i];
	}

	double avg = sum / static_cast<double>(n);
	int count = 0;
	std::list<int> l;
	for (int i = 0; i < n; ++i){
		if (temperature[i] > avg){
			++count;
			l.push_back(i);
		}
	}

	std::cout << count << std::endl;
	for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it){
		std::cout << *it << ' ';
	}
	
	system("pause");

	return 0;
}
#include <vector>
#include <string>
#include <cstdint>
#include <map>
#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

tuple<const string&, const string&, const map<Lang, string>&, const int64_t&>
GetRank(const Region& r){
	return tie(r.std_name, r.parent_std_name, r.names, r.population);
}

struct RegionCompare
{
	bool operator() (const Region& lhs, const Region& rhs) const{
		return GetRank(lhs) < GetRank(rhs);
	}
};



int FindMaxRepetitionCount(const vector<Region>& regions){
	map<Region, int, RegionCompare> counter;

	for (const Region& reg : regions){
		counter[reg] += 1;
	}

	if (counter.empty())
		return 0;

	int res = 0;

	for (const pair<Region, int>& item : counter)
		if (item.second > res)
			res = item.second;
	return res;
}

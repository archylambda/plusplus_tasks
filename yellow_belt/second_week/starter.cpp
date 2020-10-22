#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query {
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	// ���������� ��� �������
	string type_s;
	is >> type_s;
	if (type_s == "NEW_BUS"){
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (string& stop : q.stops){
			is >> stop;
		}
	}
	else if (type_s == "BUSES_FOR_STOP"){
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (type_s == "STOPS_FOR_BUS"){
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (type_s == "ALL_BUSES"){
		q.type = QueryType::AllBuses;
	}

	return is;
}

struct BusesForStopResponse {
	vector<string> buses_for_stop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	// ���������� ��� �������
	if (r.buses_for_stop.empty()){
		os << "No stop";
	}
	else{
		for (const string& bus : r.buses_for_stop){
			cout << bus << " ";
		}
	}
	return os;
}

struct StopsForBusResponse {
	// ��������� ������ ��� ���������
	string bus;
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;
	
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	// ���������� ��� �������
	if (!r.buses_to_stops.count(r.bus)){
		os << "No bus";
	}
	else{
		for (const string& stop : r.buses_to_stops.at(r.bus)){
			os << "Stop " << stop << ": ";
			if (r.stops_to_buses.at(stop).size() == 1){
				os << "no interchange";
			}
			else{
				for (const string& other_bus : r.stops_to_buses.at(stop)){
					if (r.bus != other_bus){
						os << other_bus << " ";
					}
				}
			}
			os << endl;
		}
	}
	return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	
	if (r.buses_to_stops.empty()){
		os << "No buses";
	}
	else{
		for (const auto& bus_item : r.buses_to_stops) {
			os << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				os << stop << " ";
			}
			os << endl;
		}
	}

	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		
		for (const string& stop : stops) {
			buses_to_stops[bus].push_back(stop);
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		if (stops_to_buses.count(stop)){
			return{ stops_to_buses.at(stop) };
		}
		return{ {} };

	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		if (buses_to_stops.count(bus) == 0){
			return{ bus, {}, {} };
		}
		return{ bus, buses_to_stops, stops_to_buses };
	}

	AllBusesResponse GetAllBuses() const {
		if (buses_to_stops.empty())
			return{};
		return{ buses_to_stops };
	}
private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// �� ����� ���� ������� main, ���������� ������� � ������ ����

int main() {

	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}
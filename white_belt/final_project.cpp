#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <fstream>
using namespace std;
using namespace std::chrono;
class Date {
public:
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	Date(int y, int m, int d){
		year = y;

		if (m < 1 || m > 12){
			stringstream ss;
			ss << "Month value is invalid: " << to_string(m);
			throw runtime_error(ss.str());
		}

		month = m;

		if (d < 1 || d > 31){
			stringstream ss;
			ss << "Day value is invalid: " << to_string(d);
			throw runtime_error(ss.str());
		}
		
		day = d;
		
	}


//if (!((m + d) / 100 == 0) || stream.peek() != EOF)

	friend ostream& operator<< (ostream& out, const Date& date){

		out << setfill('0') << setw(4) << date.year << '-' <<
			setfill('0') << setw(2) << date.month << '-' <<
			setfill('0') << setw(2) << date.day;

		return out;
	}

	friend bool operator<(const Date& lhs, const Date& rhs){
		return lhs.year * 365 + lhs.month * 31 + lhs.day < rhs.year * 365 + rhs.month * 31 + rhs.day;
	}
private:
	int year;
	int month;
	int day;

};

void EnsureNextSymbolAndSkip(stringstream& stream, char sym){
	if (stream.peek() != sym){
		throw exception();
	}
	stream.ignore(1);
}
void CheckStream(stringstream& stream){
	if (stream.fail()){
		throw exception();
	}
}

const char SYM = '-';

Date ParseDate(const string& date_str){
	stringstream s(date_str);
	int y = 0, m = 0, d = 0;
	try{
		s >> y;
		CheckStream(s);
		EnsureNextSymbolAndSkip(s, SYM);
		s >> m;
		CheckStream(s);
		EnsureNextSymbolAndSkip(s, SYM);
		s >> d;
		CheckStream(s);
		if (s.peek() != EOF)
			throw exception();
	}
	catch (exception& ex){
		stringstream ss;
		ss << "Wrong date format: " << date_str;
		throw runtime_error(ss.str());
	}

	return{ y, m, d };
}

class Database {
public:
	void AddEvent(const Date& date, const string& event){
		db[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event){
		bool res = false;
		if (db.count(date))
			res = db[date].erase(event);

		return res;
	}
	int DeleteDate(const Date& date){
		
		if (db.count(date) > 0){
			size_t del_cnt = db[date].size();
			db.erase(date);
			return del_cnt;
		}
		else {
			return 0;
		}
	}

	set<string> Find(const Date& date) const {
		set<string> res;
		if (db.count(date) > 0){
			res = db.at(date);
		}
		return res;
	}

	void Print() const{
		
		for (const auto& item : db){
			for (const auto& ev : item.second){
				cout << item.first << ' ' << ev << endl;
			}
		}
	}
private:
	map<Date, set<string>> db;
};

set<string> COMMANDS = {
	"Add", "Del", "Find", "Print" };

void UI(){
	Database db;

	string command;
	//ifstream file("tests.txt");
	//auto a = file.is_open();
	while (getline(cin, command)) {
		// —читайте команды с потока ввода и обработайте каждую
		try{
			stringstream ss(command);
			string action;
			ss >> action;

			if (action != ""){

				if (!COMMANDS.count(action)){
					stringstream ss;
					ss << "Unknown command: " << action;
					throw runtime_error(ss.str());
				}

				if (action == "Print"){
					db.Print();
				}
				else {
					string date_str;
					ss >> date_str;
					Date date = ParseDate(date_str);

					if (action == "Find"){
						set<string> queryRes = db.Find(date);
						for (const string& ev : queryRes)
							cout << ev << endl;
					}
					else if (action == "Del" && ss.eof()){
						cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
					}
					else {
						string event;
						ss >> event;
						if (action == "Del"){
							if (db.DeleteEvent(date, event))
								cout << "Deleted successfully" << endl;
							else
								cout << "Event not found" << endl;
						}
						else {
							db.AddEvent(date, event);
						}
					}
				}
			}
		}
		catch (exception& err){
			cout << err.what() << endl;
			break;
		}
	}
}

int main() {

	UI();
	
	//system("pause");
	return 0;
};


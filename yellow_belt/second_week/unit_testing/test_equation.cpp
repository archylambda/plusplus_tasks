#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
	if (a == 0){
		if (b != 0)
			//bx + c = 0, bx = 0
			return 1;
		else{
			return 0;
		}
	}
	if (b == 0){
		if (c == 0){
			//ax^2 = 0
			return 1;
		}
		else{
			if (a < 0 && c < 0 || a > 0 && c > 0)
			// x^2 + 5 = 0, -5x^2 - 5 = 0 	
				return 0;
			else
			// x^2 - 4 = 0
				return 2;
		}
	}
	double D = b*b - 4 * a*c;
	if (D > 0)
		return 2;

	if (D < 0)
		return 0;
	//D == 0
	return 1;
}

void TestLinear(){
	AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "128");
	AssertEqual(GetDistinctRealRootCount(0, -1, 12), 1, "129");
	AssertEqual(GetDistinctRealRootCount(0, -15, 2), 1, "130");
	AssertEqual(GetDistinctRealRootCount(0, 0, 2), 0, "131");
}

void TestCutQuad(){
	// b == 0
	AssertEqual(GetDistinctRealRootCount(1, 0, 3), 0, "139");
	AssertEqual(GetDistinctRealRootCount(-1, 0, -3), 0, "140");
	AssertEqual(GetDistinctRealRootCount(-1, 0, 3), 2, "141");
	AssertEqual(GetDistinctRealRootCount(1, 0, -3), 2, "142");
	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "143");
}

void TestFullQuad(){
	// x^2 + 4x + 4 = 0
	AssertEqual(GetDistinctRealRootCount(3, 4, 1), 2, "149");
	AssertEqual(GetDistinctRealRootCount(3, 1, 4), 0, "150");
	AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1, "151");
	
}


int main() {
	TestRunner runner;
	runner.RunTest(TestLinear, "TestLinear");
	runner.RunTest(TestCutQuad, "TestCutQuad");
	runner.RunTest(TestFullQuad, "TestFullQuad");

	return 0;
}
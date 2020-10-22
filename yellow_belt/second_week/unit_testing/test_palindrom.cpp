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

bool IsPalindrom(const string& str) {
	return true;
}


void TestPredefined(){
	Assert(IsPalindrom(""), "empty string is palindrom");
	Assert(IsPalindrom(" "), "one symbol string is palindrom");
	Assert(IsPalindrom("#"), "one symbol string is palindrom");
	Assert(IsPalindrom("_"), "one symbol string is palindrom");
	Assert(IsPalindrom("1"), "one symbol string is palindrom");
	Assert(IsPalindrom("qwe/ewq"), "1c");
	Assert(IsPalindrom("qwe ewq"), "2c");
	Assert(IsPalindrom("123::321"), "3c");
	Assert(IsPalindrom("123:321"), "4c");
	Assert(IsPalindrom(" 123::321 "), "5c");
	Assert(IsPalindrom("  "), "6c");
	Assert(IsPalindrom("   "), "7c");

	Assert(!IsPalindrom("123:123"), "1w");
	Assert(!IsPalindrom("123::123"), "2w");
	Assert(!IsPalindrom("a123::321"), "3w");
	Assert(!IsPalindrom("123::321b"), "4w");
	Assert(!IsPalindrom("123::321b "), "5w");
	Assert(!IsPalindrom(" 123::321b"), "6w");
	Assert(!IsPalindrom(" _  "), "7w");
	
	

}

int main() {
	TestRunner runner;
	runner.RunTest(TestPredefined, "TestPredefined");
	return 0;
}
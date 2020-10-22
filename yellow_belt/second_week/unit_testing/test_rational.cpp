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

//class Rational {
//public:
//
//	Rational();
//	Rational(int numerator, int denominator) {
//	}
//
//	int Numerator() const {
//	}
//
//	int Denominator() const {
//	}
//};

void TestRational(){
	Rational r1;
	AssertEqual(r1.Numerator(), 0,"base num must be 0");
	AssertEqual(r1.Denominator(), 1, "base denom must be 1");

	Rational r2(1, 3);
	AssertEqual(r2.Numerator(), 1, "num of 1/3 must be 1");
	AssertEqual(r2.Denominator(), 3, "denom of 1/3 must be 3");

	Rational r3(-1, 3);
	AssertEqual(r3.Numerator(), -1, "num of -1/3 must be -1");
	AssertEqual(r3.Denominator(), 3, "denom of -1/3 must be 3");

	Rational r4(1, -3);
	AssertEqual(r4.Numerator(), -1, "num of 1/-3 must be -1");
	AssertEqual(r4.Denominator(), 3, "denom of 1/-3 must be 3");
	
	Rational r5(5, 15);
	AssertEqual(r5.Numerator(), 1, "num of 5/15 must be 1");
	AssertEqual(r5.Denominator(), 3, "denom of 5/15 must be 3");

	Rational r6(-5, 15);
	AssertEqual(r6.Numerator(), -1, "num of -5/15 must be -1");
	AssertEqual(r6.Denominator(), 3, "denom of -5/15 must be 3");

	Rational r7(5, -15);
	AssertEqual(r7.Numerator(), -1, "num of 5/-15 must be -1");
	AssertEqual(r7.Denominator(), 3, "denom of 5/-15 must be 3");

	Rational r8(-2, -3);
	AssertEqual(r8.Numerator(), 2, "num of -2/-3 must be 2");
	AssertEqual(r8.Denominator(), 3, "denom of -2/-3 must be 3");

	Rational r9(-12, -40);
	AssertEqual(r9.Numerator(), 3, "num of -12/-40 must be 3");
	AssertEqual(r9.Denominator(), 10, "denom of -12/-40 must be 10");

	Rational r10(0, -40);
	AssertEqual(r10.Numerator(), 0, "num of 0/-40 must be 0");
	AssertEqual(r10.Denominator(), 1, "denom of 0/-40 must be 1");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestRational, "TestReational");
	
	return 0;
}
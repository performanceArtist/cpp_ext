#include <iostream>
#include <vector>
//std::accumulate
#include <numeric>
#include <string>

#include "Func.h"


void calc1(std::function <bool(int, int)> cb) {
	if(cb(5, 3)) std::cout << "Yep1\n";
}

void checkZip() {
	std::vector<int> a = { 1,2,3};
	std::vector<char> b = { 'a', 'b', 'c' };

	auto charint = [](int a, char b)->std::string {
		std::string s;

		char aChar = '0' + a;
		s.push_back(aChar);
		s.push_back(b);
		return s;
	};

	//std::cout << charint(5, 'a');
	std::vector<std::string> res = func::zipWith (a, b, charint);

	std::cout << res[0];
}

int main() {
	auto min = [](int x, int y)-> bool{return x>y;};
	
	if(min(5, 3)) std::cout << "Yep\n";
	calc1(min);
	
	std::vector <int> v = {1,2,57,8,9,4};
	//std::transform(v.begin(), v.end(), v.begin(), [](int el) {return el+1;});
	//std::for_each(v.begin(), v.end(), [](int el) {std::cout << el << " ";});
	
	auto echo = [](int el) {std::cout << el << " ";};
	auto inc = [](int el) {return el+1;};
	
	func::forEach(v, echo);
	v = func::map(v, inc);
	func::forEach(v, echo);
	
	bool t = func::any(v, [](int el) -> bool {return el > 10; });
	bool t1 = func::all (v, [](int el) -> bool {return el > 2; });
	bool full = std::any_of(v.begin(), v.end(), [](int el) -> bool {return el > 10; });
	if (t) std::cout << "d";
	if (t1) std::cout << "f";

	auto plus = [](int acc, int el)->int { return acc + el; };
	int sum = std::accumulate(v.begin(), v.end(), 0, plus);
	int sum1 = func::reduce(v, plus, 0);
	std::cout << sum << " " << sum1;

	checkZip();
	func::hmm(56, 'a');
	return 0;
}
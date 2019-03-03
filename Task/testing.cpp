#include <iostream>
#include <chrono>

#include "Task.h"

int main() {
	
	auto ms = 0;
	

	Task myClock([&](Task* task) {
		std::cout << task->track << "\n";
		//begin = std::chrono::high_resolution_clock::now();
	}, 1000);

	auto begin = std::chrono::high_resolution_clock::now();

	while (true) {
		myClock.run(ms);
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	}

	return 0;
}
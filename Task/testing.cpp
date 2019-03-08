#include <iostream>
#include <chrono>
#include <string>

#include "Task.h"

int main() {

	Task myClock([](Task* task) {
		std::cout << task->track << "\n";
	}, 1000);

	Task spawnEnemy([](Task* task) {
		if (task->track < 10) {
			std::cout << task->track << " New enemy!\n";
		}
		else {
			//increase spawn frequency every 10 calls
			std::cout << "Faster!\n";
			unsigned int tm = task->getTimeout();
			if (tm > 200) task->setTimeout(tm - 200);
			task->track = 0;
		}
	}, 1000);

	Task runTwice([](Task* task) {
		std::cout << task->track << "\n";
		if (task->track >= 2) {
			task->disable();
			std::cout << "Stop";
		}
	}, 1000);

	Task swap([](Task* task) {
		std::cout << task->track << "\n";
		if (task->track > 5) {
			std::cout << "And now for something completely different...\n";
			task->setCallback([](Task* task) {
				std::cout << "Shazam!\n";
			});
		}
	}, 1000);

	std::string myStr = "Hi there!";

	Task manage([](Task* task) {
		std::cout << *((std::string*)task->target) << "\n";
	}, 1000);

	manage.bind(&myStr);

	auto ms = 0;
	auto begin = std::chrono::high_resolution_clock::now();

	while (true) {
		myClock.run(ms);
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = end - begin;
		ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
	}

	return 0;
}
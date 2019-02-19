/*
An implementaion of the philosphers dinner problem using each thread to run a philospoher
the user enters a number of philosphers each of whom run a dine method on there own thread, they try to take both forks either side of them in order to eat
if one of the forks is already in use the philosopher with wait until it is free and then take it to use.
*/

#include <thread>
#include <vector>
#include "Philosopher.h"

int main() {
	int no_of_philosophers = 0;
	while (no_of_philosophers < 2) {
		std::cout << "Enter number of philosophers to attend the dinner(min 2) and press enter: " << std::endl;
		std::cin >> no_of_philosophers;
	}
	int lengthOfDinner;
	std::cout << "Enter length of dinner(seconds) and press enter: " << std::endl;
	std::cin >> lengthOfDinner;

	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Dinner started!" << std::endl;


	Table table(no_of_philosophers);
	std::vector<Philosopher*> philosophers;
	//make philosophers and have them at table
	for (int i = 0; i < no_of_philosophers; ++i) {
		if (i == no_of_philosophers - 1) {
			philosophers.push_back(new Philosopher(i, table, table.forks.at(i), table.forks.at(0)));
		}
		else {
			philosophers.push_back(new Philosopher(i, table, table.forks.at(i), table.forks.at(i + 1)));
		}
	}
	

	table.ready = true;
	std::this_thread::sleep_for(std::chrono::seconds(lengthOfDinner));
	table.ready = false;

	//clean up philosopher pointers
	while (philosophers.size() > 0) {
		delete philosophers.back();
		philosophers.pop_back();
	}
	//dinner over
	std::cout << "Dinner done, Press any key to exit." << std::endl;
	std::cin.ignore();
	std::cin.ignore();
}
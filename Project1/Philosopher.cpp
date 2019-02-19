#include "Philosopher.h"

void Philosopher::dine()
{
	//wait for table to be ready
	while (!table.ready);

	//once ready continue until no longer ready
	while (table.ready) {
		think();
		eat();
	}
}

void Philosopher::eat()

{
	//keep trying to get forks
	while (!leftFork.pickUp()) {/* table.print("philosopher: " + std::to_string(id) + " waiting on Fork: " + std::to_string(leftFork.forkId));*/ }
	while (!rightFork.pickUp()) {/* table.print("philosopher: " + std::to_string(id) + " waiting on Fork: " + std::to_string(rightFork.forkId));*/ }

	table.print("Philosopher: " + std::to_string(id) + " started eating with Forks: " + std::to_string(leftFork.forkId)
		+ "," + std::to_string(rightFork.forkId));

	//eat for a bit
	static thread_local std::uniform_int_distribution<> dist(1, 6);
	std::this_thread::sleep_for(std::chrono::milliseconds(dist(rng) * 50));

	//release both forks
	leftFork.putDown();
	rightFork.putDown();
	table.print("Philosopher: " + std::to_string(id) + " finished eating.");
}

void Philosopher::think()
{
	table.print("Philosopher: " + std::to_string(id) + " is thinking.");
	//think a bit
	static thread_local std::uniform_int_distribution<> wait(1, 6);
	std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));

	table.print("Philosopher: " + std::to_string(id) + " stoped thinking.");
}

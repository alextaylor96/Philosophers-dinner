#include <string>
#include <random>
#include "Fork.h"
#include "Table.h"

#pragma once
class Philosopher
{

private:
	int const id;
	Table&     table;
	Fork&             leftFork;
	Fork&             rightFork;
	std::thread       lifethread;
	std::mt19937      rng{ std::random_device{}() };
public:
	Philosopher(int id, Table &table, Fork &l, Fork &r) :
		id(id), table(table), leftFork(l), rightFork(r), lifethread(&Philosopher::dine, this) {}

	~Philosopher()
	{
		lifethread.join();
	}

	Philosopher(const Philosopher& other):id(other.id), table(other.table),leftFork(other.leftFork), rightFork(other.rightFork){}
	Philosopher(Philosopher&&) = default;
	Philosopher& operator=(const Philosopher&) = default;

	void dine()
	{
		//wait for table to be ready
		while (!table.ready);

		//once ready continue until no longer ready
		while (table.ready){
			think();
			eat();
		}
	}

	void eat()
	{
		//keep trying to get forks
		while (!leftFork.pickUp()) {/* table.print("philosopher: " + std::to_string(id) + " waiting on Fork: " + std::to_string(leftFork.forkId));*/ }
		while(!rightFork.pickUp()) {/* table.print("philosopher: " + std::to_string(id) + " waiting on Fork: " + std::to_string(rightFork.forkId));*/ }

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

	void think()
	{
		table.print("Philosopher: " + std::to_string(id) + " is thinking.");
		//think a bit
		static thread_local std::uniform_int_distribution<> wait(1, 6);
		std::this_thread::sleep_for(std::chrono::milliseconds(wait(rng) * 150));

		table.print("Philosopher: " + std::to_string(id) + " stoped thinking.");
	}
};



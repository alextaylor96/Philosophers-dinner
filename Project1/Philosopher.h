//philosopher which attend dinner
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

	//philosopher attends the dinner and thinks/eats
	void dine();

private:
	void eat();

	void think();
};



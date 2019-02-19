//Table used in dinner, contains all the forks
#include <iostream>
#include "Fork.h"

#pragma once


class Table
{
public:

	Table(int size) : tableSize(size) {
		for (int i = 0; i < tableSize; ++i) {
			forks.push_back(Fork(i));
		}
	};

	~Table() {};

	std::vector<Fork> forks;
	
	void print(std::string toPrint) {
		//use table to print so cout is locked and output makes sence
		std::lock_guard<std::mutex> guard(printLock);
		std::cout << toPrint << std::endl;
	}
	
	bool ready = false;


private:
	std::mutex printLock;
	int tableSize;
};


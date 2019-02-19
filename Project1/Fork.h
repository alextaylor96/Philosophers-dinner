//fork to be used by people at the dinner
#include <mutex>
#pragma once

class Fork {
public:
	Fork(int id) : forkId(id){}
	~Fork() {}

	Fork(const Fork& other):forkId(other.forkId){}
	Fork(Fork&&) = default;
	Fork& operator=(const Fork&) = default;

	bool pickUp() {
		return inUse.try_lock();
	}

	bool putDown() {
		inUse.unlock();
		return false;
	}

	int const forkId;

private:
	std::mutex inUse;
};
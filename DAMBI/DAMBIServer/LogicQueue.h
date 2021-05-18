#pragma once
#include <mutex>
#include <queue>
class LogicQueue {
private:
	std::mutex mtx;
	std::queue<int*> Logicqueue;
public:
	LogicQueue();
	bool isEmpty();
	void Pop();
	void Push(int* data);
};

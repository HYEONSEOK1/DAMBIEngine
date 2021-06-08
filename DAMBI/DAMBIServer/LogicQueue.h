#pragma once
#include <mutex>
#include <queue>
#include "stdafx.h"
#include "QueueCapsule.h"

class LogicQueue {
private:
	std::mutex mtx;
	std::queue<QueueCapsule*> Logicqueue;
public:
	LogicQueue();
	bool isEmpty();
	QueueCapsule* Pop();
	void Push(QueueCapsule* data);
};

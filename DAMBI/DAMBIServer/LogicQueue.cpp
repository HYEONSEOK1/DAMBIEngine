#include <queue>
#include "LogicQueue.h"
LogicQueue::LogicQueue()
{

}
bool LogicQueue::isEmpty()
{
    return LogicQ.empty();
}

void LogicQueue::Pop()
{
    mtx.lock();
    if (!LogicQ.empty())
    {
        LogicQ.pop();
    }
    mtx.unlock();
}

void LogicQueue::Push(int* data)
{
    mtx.lock();
    LogicQ.push(data);
    mtx.unlock();
}
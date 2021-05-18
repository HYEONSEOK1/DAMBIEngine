#include <queue>
#include "LogicQueue.h"
LogicQueue::LogicQueue()
{

}
bool LogicQueue::isEmpty()
{
    return Logicqueue.empty();
}

void LogicQueue::Pop()
{
    mtx.lock();
    if (!Logicqueue.empty())
    {
        Logicqueue.pop();
    }
    mtx.unlock();
}

void LogicQueue::Push(int* data)
{
    mtx.lock();
    Logicqueue.push(data);
    mtx.unlock();
}
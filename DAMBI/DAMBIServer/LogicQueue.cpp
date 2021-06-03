#include <queue>
#include "LogicQueue.h"
#include "QueueCapsule.h"

LogicQueue::LogicQueue()
{

}
bool LogicQueue::isEmpty()
{
    return Logicqueue.empty();
}

QueueCapsule* LogicQueue::Pop()
{
    QueueCapsule* data = NULL;
    mtx.lock();
    if (!Logicqueue.empty())
    {
        data = Logicqueue.front();
        Logicqueue.pop();
    }
    mtx.unlock();
    return data;
}

void LogicQueue::Push(QueueCapsule* data)
{
    mtx.lock();
    Logicqueue.push(data);
    mtx.unlock();
}
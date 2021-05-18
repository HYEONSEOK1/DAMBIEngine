#include "extern.h"
#include "stdafx.h"
#include "MainConfig.h"
#include "ClientObject.h"
#include "Protocols.h"
#include "LogicQueue.h"
#include <list>
typedef struct RECV_MSG
{
	int		flag;
	ClientObject* pClientObject;
	stOverEx* ExData;
	int		Size;
}RECV_MSG;
std::list<RECV_MSG*> RecvQueue;
std::mutex RecvQueueMutex;
void AddRecvQueue(int flag, ClientObject* pClientObject, stOverEx* ExData, int Size)
{
	RECV_MSG* pRecv = new RECV_MSG;
	
	pRecv->flag = flag;
	pRecv->pClientObject = pClientObject;
	pRecv->ExData = ExData;
	pRecv->Size = Size;

	RecvQueueMutex.lock();
	RecvQueue.push_back(pRecv);
	RecvQueueMutex.unlock();
}
void RecvThread()
{
	while (1)
	{
		if (!RecvQueue.empty())
		{
			RecvQueueMutex.lock();
			RECV_MSG* pRecv = RecvQueue.front();
			RecvQueueMutex.unlock();

			ClientObject* pClientObject = pRecv->pClientObject;
			stOverEx* ExData = pRecv->ExData;
			//pLogicQueue->Push(0, PACKET_SEND, pClientObject, ExData);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}
void WorkerThread(HANDLE hIOCP) {

	HANDLE IoCompletionPort = (HANDLE)hIOCP;
	SOCKET sock;
	DWORD  bytesTrans;
	DWORD flags = 0;
	OVERLAPPED_ENTRY entry;
	bool bResult = false;
	memset(&entry, 0, sizeof(entry));
	HMODULE hModule = ::GetModuleHandle(L"kernel32.dll");
	while (true) {
		bResult = GetQueuedCompletionStatus(IoCompletionPort, &entry.dwNumberOfBytesTransferred, &entry.lpCompletionKey, &entry.lpOverlapped, INFINITE);
		int a;
		if (bResult)
		{
			DWORD IocpSize = entry.dwNumberOfBytesTransferred;
			LPOVERLAPPED lpOverlapped = entry.lpOverlapped;
			ClientObject* pClientObject = (ClientObject*)entry.lpCompletionKey;
			stOverEx* ExData = (stOverEx*)lpOverlapped;

			if (lpOverlapped == pClientObject->GetOverlapped()) // recv buffer
			{
				if (IocpSize == 0)
				{
					std::cout << "error" << std::endl;
				}
				else
				{
					AddRecvQueue(0, pClientObject, ExData, IocpSize);
					
				}
			}
		}
	}
}


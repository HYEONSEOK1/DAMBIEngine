#include "extern.h"
#include "stdafx.h"
#include "MainConfig.h"
#include "ClientObject.h"
#include "Protocols.h"
#include "LogicQueue.h"
#include "QueueCapsule.h"
#include <list>
typedef struct RECV_MSG
{
	int		flag;
	ClientObject* pClientObject;
	stOverEx* ExData;
	int		Size;
}RECV_MSG;
typedef struct msg {
	int number;
	int age;
	char packet[10];
	msg() { Init(); }
	void Init()
	{
		memset(this, 0, sizeof(msg));
	}
}msg;
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
			RecvQueue.pop_front();
			RecvQueueMutex.unlock();
		

			ClientObject* pClientObject = pRecv->pClientObject;
			stOverEx* ExData = pRecv->ExData;
			pClientObject->m_nRecvLength += pRecv->Size;
			
			LOG_INFO("  [RECV] CMD_PACKET(0x0001), len:30] [FROM] [UserIndex:%d]", pClientObject->unuserIndex);

			BOOL bMoveFoward = FALSE;
			BYTE* pRead = pClientObject->pRecvBuffer;
			PS_PACKET_HEADER pHead;
			int nPacketLength = 0;
			while (TRUE) {
				if (pClientObject->m_nRecvLength < sizeof(S_PACKET_HEADER)) { bMoveFoward = TRUE; break; }		// 헤더사이즈보다 작은 데이터 -> 버퍼링

				pHead = (PS_PACKET_HEADER)pRead;
				
					char strMsg[256] = { 0 };
					int pos = 0;
					for (int i = 0; i < sizeof(S_PACKET_HEADER); i++) {
						BYTE* ptr = (BYTE*)pHead;
						//pos += _stprintf_s(strMsg + pos, 256 - pos, _T("%02X:"), (BYTE)ptr[i]);
					}
					
				nPacketLength = pHead->unLen;
				
				if (static_cast<int>(pClientObject->m_nRecvLength) < nPacketLength) { bMoveFoward = TRUE; break; }				// 수신된 바이트수가 작다 -> 버퍼링
				message m;
				LPBYTE pBody = (LPBYTE)(pRead + sizeof(S_PACKET_HEADER));
				InLogicQueue(0, pHead->unCmd, pClientObject, pBody, pHead->unLen);
				
				if ((pClientObject->m_nRecvLength -= nPacketLength) == 0) 
					break;	// 처리 완료
				else pRead += nPacketLength;								
		
			}

			if (bMoveFoward && pClientObject->pRecvBuffer != pRead) 
				memcpy(pClientObject->pRecvBuffer, pRead, pClientObject->m_nRecvLength);	// 버퍼에 남은 데이터를 앞으로 이동


			DWORD dwBytes = 0;
			DWORD dwFlags = 0;
			if (WSARecv(pClientObject->GetClientSocket(), pClientObject->GetWsaBuf(pClientObject->pRecvBuffer + pClientObject->m_nRecvLength,
				G_MAX_NETWORK_LENGTH - pClientObject->m_nRecvLength), 1, &dwBytes, &dwFlags, pClientObject->GetOverlapped(), NULL) == SOCKET_ERROR
				&& WSAGetLastError() != WSA_IO_PENDING)
			{
				int a = 3;
			}
			

		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
	std::thread* pthread;
	pthread = new std::thread(RecvThread);

	memset(&entry, 0, sizeof(entry));
	HMODULE hModule = ::GetModuleHandle(L"kernel32.dll");
	while (true) {
		bResult = GetQueuedCompletionStatus(IoCompletionPort, &entry.dwNumberOfBytesTransferred, &entry.lpCompletionKey, &entry.lpOverlapped, INFINITE);
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
					pMainConfig->count--;
				}
				else
				{
					AddRecvQueue(0, pClientObject, ExData, IocpSize);
					
				}
			}
		}
	}
}


#include "stdafx.h"
#include "extern.h"
#include "ClientObject.h"
#include "ServerObject.h"
ClientObject::ClientObject()
{
	memset(&RecvBuffer.m_wsaOver, 0, sizeof(WSAOVERLAPPED));
	pRecvBuffer = new BYTE[G_MAX_NETWORK_LENGTH];
	m_nRecvLength = 0;
}

ClientObject::~ClientObject()
{
}

void ClientObject::SetClientSocket(SOCKET ClientSocket)
{
	Socket = ClientSocket;
}

void ClientObject::SetClientInfo(const std::string Addr, const UINT Port, int userIndex)
{
	strClientAddr = Addr;
	ClientPort = Port;
	unuserIndex = userIndex;
}

void ClientObject::SetRecvStatus()
{
	BOOL bSockOpt = TRUE;
	setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, (char*)&bSockOpt, sizeof(bSockOpt));

	int nSockBufSize = 8192; 
	setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSockBufSize, sizeof(nSockBufSize));

	// register IOCP Port
	if (CreateIoCompletionPort((HANDLE)Socket, pServerObject->GetIocpPort(), (ULONG_PTR)this, 0) == NULL)
	{
		std::cout << "CreateIoCompletionPort Fail " << WSAGetLastError() << std::endl;
		return;
	}
	DWORD dwBytes = 0, dwFlags = 0;


	if (WSARecv(Socket, GetWsaBuf(pRecvBuffer, MAX_BUF_SIZE), 1, &dwBytes, &dwFlags, &RecvBuffer.m_wsaOver, NULL) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) 
		{
			std::cout << "WSARecv Fail " << WSAGetLastError() << std::endl;
			return;
		}
	}
}


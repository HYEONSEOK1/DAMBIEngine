#include "stdafx.h"
#include "extern.h"
#include "ClientObject.h"
#include "MainConfig.h"

void AcceptThread(SOCKET ServerSocket) {
	while (!pMainConfig->getThreadEnd()) {
		ClientObject* cObject = NULL;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));


		SOCKET Socket;
		struct sockaddr_in ClientAddr;
		int ClientAddrSize = sizeof(ClientAddr);
		Socket = WSAAccept(ServerSocket, (struct sockaddr*)&ClientAddr, &ClientAddrSize, NULL, NULL);
		if (Socket == INVALID_SOCKET) {
		
			LOG_ERROR("Accept Fail!");
			continue;
		}
		cObject = new ClientObject;
		std::string strClientAddr;
		UINT ClientPort;
		strClientAddr = inet_ntoa(ClientAddr.sin_addr);
		ClientPort = ntohs(ClientAddr.sin_port);
		cObject->SetClientSocket(Socket);
		cObject->SetClientInfo(strClientAddr, ClientPort);
		cObject->SetRecvStatus();
	}
}


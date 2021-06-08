#pragma once
#define MAX_BUF_SIZE 300000
struct stOverEx {
	WSAOVERLAPPED m_wsaOver;
	WSABUF m_wsaBuf;
	unsigned char m_IOCPbuf[MAX_BUF_SIZE];// IOCP send/recv 버퍼
	DWORD m_Operation; // Send/Recv/Accept 구별 

};
const int G_MAX_NETWORK_LENGTH = (1024 * 1024);	// 클라이언트 통신에서 사용하는 버퍼 크기
class ClientObject
{
private:
	SOCKET Socket;
	std::string strClientAddr;
	UINT ClientPort;
	stOverEx RecvBuffer;
	
public:
	UINT unuserIndex;
	BYTE* pRecvBuffer;
	UINT m_nRecvLength;		
	ClientObject();
	~ClientObject();
	OVERLAPPED* GetOverlapped() {
		return &(RecvBuffer.m_wsaOver);
	}
	WSABUF* GetWsaBuf(LPBYTE pBuff, UINT unLen) {
		RecvBuffer.m_wsaBuf.buf = (char*)pBuff;
		RecvBuffer.m_wsaBuf.len = unLen;
		return &(RecvBuffer.m_wsaBuf);
	}
	SOCKET GetClientSocket() { return Socket; };
	void SetClientSocket(SOCKET ClientSocket);
	void SetClientInfo(const std::string Addr, const UINT Port, int userIndex);
	void SetRecvStatus();
};


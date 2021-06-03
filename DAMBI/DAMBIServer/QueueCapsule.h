#pragma once
#define IOCP_ONREAD				1
#define IOCP_ONCLOSE			99

class ClientObject;
struct QueueCapsule
{
	QueueCapsule(const void* pData, UINT unSize, BOOL bAlloc = TRUE);	// 
	virtual ~QueueCapsule();

	BYTE m_bAlloc;
	BYTE* m_pBuffer;
	UINT m_nLength;
	USHORT m_unType;
	USHORT m_unCommand;

	ClientObject* m_pClientObject;
};

BOOL InLogicQueue(USHORT unType, USHORT unCmd, ClientObject* pContext, BYTE* pData = NULL, UINT unSize = 0);

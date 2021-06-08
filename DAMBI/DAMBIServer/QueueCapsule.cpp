#include "stdafx.h"
#include "extern.h"
#include "QueueCapsule.h"
#include "ClientObject.h"
#include "Protocols.h"
#include "LogicQueue.h"
QueueCapsule::QueueCapsule(const void* pData, UINT unSize, BOOL bAlloc /*= FALSE*/)
{
	m_pBuffer = NULL;
	m_nLength = 0;
	m_bAlloc = bAlloc;
	if (pData == NULL || unSize == 0) return;

	if (m_bAlloc) {
		if ((m_pBuffer = new BYTE[unSize]) == NULL) {
			m_bAlloc = 0;
			return;
		}
		m_nLength = unSize;
		CopyMemory(m_pBuffer, pData, m_nLength);
	}
	else {
		m_nLength = unSize;
		m_pBuffer = (BYTE*)pData;
	}
}

QueueCapsule::~QueueCapsule()
{
	if (m_bAlloc)
		delete(m_pBuffer);
}
BOOL InLogicQueue(USHORT unType, USHORT unCommand, ClientObject* pContext, BYTE* pData, UINT unSize)
{
	message m;

	QueueCapsule* pCapsule = new QueueCapsule(pData, unSize);
	if (pCapsule) {
		pCapsule->m_pClientObject = pContext;
		pCapsule->m_unType = unType;
		pCapsule->m_unCommand = unCommand;
		pLogicQueue->Push(pCapsule);
	}

	return TRUE;

}
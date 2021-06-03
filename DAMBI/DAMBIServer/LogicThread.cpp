#include "extern.h"
#include "stdafx.h"
#include "MainConfig.h"
#include "LogicQueue.h"
#include "Protocols.h"
void LogicThread() {
	while (true) {
	
		if (!pLogicQueue->isEmpty())
		{
			QueueCapsule* data = pLogicQueue->Pop();
			if (data->m_unCommand == PACKET_SEND)
			{
				message* msg = (message*)(data->m_pBuffer);
				int a = 3;
			}
			
		}
		else

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}
}


#include "extern.h"
#include "stdafx.h"
#include "MainConfig.h"
#include "LogicQueue.h"
void LogicThread() {
	while (true) {
	
		if (!pLogicQueue->isEmpty())
		{
			pLogicQueue->Pop();
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
}


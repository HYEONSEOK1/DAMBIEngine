#include "stdafx.h"
#include "MainConfig.h"
#include <vector>

MainConfig::MainConfig()
{
	ThreadEnd = false;
	count = 0;
}

void MainConfig::setThreadEnd()
{
	ThreadEnd = true;
}

bool MainConfig::getThreadEnd()
{
	return ThreadEnd;
}

#include "stdafx.h"
#include "MainConfig.h"
#include <vector>

MainConfig::MainConfig()
{
	ThreadEnd = false;
}

void MainConfig::setThreadEnd()
{
	ThreadEnd = true;
}

bool MainConfig::getThreadEnd()
{
	return ThreadEnd;
}

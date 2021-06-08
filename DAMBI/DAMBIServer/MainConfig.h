#pragma once
class MainConfig
{
private:
	bool ThreadEnd;
	
	std::vector<std::thread*> WorkerThreadList;
public:
	int count;
	std::vector<std::thread*> ThreadList;
	MainConfig();
	void setThreadEnd();
	bool getThreadEnd();
};


#include "extern.h"
#include "stdafx.h"
#include "threads.h"

void InitQueue() 
{
	LogicQueue =  new std::queue<int>;
}
void InitThread()
{
	std::thread* Logic = new std::thread(Logicthread);

}
int main()
{
	std::cout << "Server Start!" << std::endl;

	/*
	
	todo : init �Լ� ����� �α� �ۼ��ϰԲ� ������. �ַܼκ��� ���� ������
	
	*/
	InitQueue();
	InitThread();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		// todo : thread�� �� �������� ���α׷��� ����ǰ� ���ִ°͵� �����ϰ�, ctrl + c �������� �����ϴ� �͵� ������.
		// �翬�� ctrl + c ������ �������Ŵ� ���� ������ ������ ó���ϴ� �Ŵ� ó���� �� �� ó���ϰ� ���� ���Ѿ� ����? Ÿ�̹� �߿�
	}

	std::cout << "Server Stop!" << std::endl;
	return 0;
}
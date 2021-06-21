# DAMBI Engine
<div align="center">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/Dmabi.png"><br><br>
</div>

-----------------

Introduction
-----------------
  **Dambi Engine** is an Open Source SW Project for Game server architecture. **Dambi Engine** provides architecture to help users to make fast-working server through some techniques. **Dambi Engine** uses standard C++ libraries and Window APIs to make sure of stable environment.
  
* There are Several techniques we used.
  
  * Multi-Threading - Divided functions by their features. It helps program works more faster.
 
  * IOCP - Windows I/O model with great performance.
 
  * Lock-free Queue - C++ template libraries for multi-core processor.

Who needs Dambi?
-----------------
* who has difficulty with starting game server
* who wnats to make multi-player game with his local device
* everyone who is interested in developing game! 
 
 What can I do with Dambi?
-----------------
**Dambi Engine** provides basic game server architecture with several threads and objects. Users can build server with adding additional features everything they need and accept their clients through their customized server environment.
 
-----------------
If You want to check out more details about our project, Please read our [Proposal Report](CONTRIBUTING.md)

-----------------

Installation
-----------------
Dmabi engine is a framework working on **Window OS** and **Standard C++** in visual studio IDE.

Plaese download the project and build through IDE.

* Check all the header and source files are in the right folder
<div align="left">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/files.PNG"><br><br>
</div>

* To use Lock-free queue provided by intel open source, Please download the [tbb](https://github.com/oneapi-src/oneTBB) and add to external libraries.
<div align="left">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install1.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install2.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install3.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install4.png"><br><br>
  
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install5.png"><br><br>
</div>


* Fill your own server IP & Port

```bash
//main.init()
if (!pServerObject->CreateSocket("your own IP", your own Port num))
{
	LOG_ERROR("Create Server Socket Error");
	return;
}
```


* Build a project to make .exe file
<img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/install6.png"><br><br>

How can I Customize my own Server?
-----------------
* In case of CPU acceleration, the number of worker threads can be set as sysinfo.dwNumberOfProcessors*2.
```bash
std::thread* Worker;
	for (int i = 0; i < sysinfo.dwNumberOfProcessors; i++)
	{
		Worker = new std::thread(WorkerThread, pServerObject->GetIocpPort());
		pMainConfig->ThreadList.push_back(Worker);
	}
```

* Set Socket Buffer Size
```bash
int nSockBufSize = 8192; 
	setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, (const char*)&nSockBufSize, sizeof(nSockBufSize));

```

* client socket buffer size(NETWORK LENGTH)
```bash
const int G_MAX_NETWORK_LENGTH = (1024 * 1024);	

```

* change your queue(std::queue or tbb::concurrent_priority_queue)
```bash
tbb::concurrent_priority_queue<QueueCapsule*, std::greater<int>> Logicqueue;
std::queue<QueueCapsule*> Logicqueue;
```

* How to use lock-free-queue
```bash
#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_queue.h>
 
int _tmain(int argc, _TCHAR* argv[])
{
    tbb::concurrent_queue<int> queue;
 

    queue.push(i);
 
    int num;
    while (queue.try_pop(num))
        std::cout << num << " ";
 
    return 0;
}
```
* Comparison of logicQueue speed by number of workerthreads (unit: ms)  


||1|2|4|8|
|------|---|---|---|---|
|std lock(mutex)|4782|8468|12535|17151|
|lock-free(tbb)|5389|5215|4318|2671

* You can change the overlapped struct your way.
```bash
	BYTE* pRecvBuffer;
	UINT m_nRecvLength;
	OVERLAPPED* GetOverlapped() {
		return &(RecvBuffer.m_wsaOver);
	}
	WSABUF* GetWsaBuf(LPBYTE pBuff, UINT unLen) {
		RecvBuffer.m_wsaBuf.buf = (char*)pBuff;
		RecvBuffer.m_wsaBuf.len = unLen;
		return &(RecvBuffer.m_wsaBuf);
	}
```

* You can customize it by adding your own threads.
```bash
#pragma once
void LogicThread();
void LogThread();
void WorkerThread(HANDLE hIOCP);
void AcceptThread(SOCKET ServerSocket);
```

* Except for winsock, standard C++ is used, so you can make it work on other operating systems if you want. (For example on Linux, just add epoll)
```bash
stdafx.h
#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <string>
#include <queue>
#include <mutex>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_queue.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <WinSock2.h>
#include "Logger.h"
```


* You can create your own protocol by adding commands and structs.
```bash
#pragma once
typedef enum CMD
{
	PACKET_SEND = 0x0001,
};
typedef struct S_PACKET_HEADER
{
	USHORT	unCmd;
	UINT	unLen;
	S_PACKET_HEADER() {
		ZeroMemory(this, sizeof(S_PACKET_HEADER));
	}
} S_PACKET_HEADER, * PS_PACKET_HEADER;

typedef struct PACKET {
	int number;
	int age;
	char packet[10];
	PACKET() { Init(); }
	void Init()
	{
		memset(this,0, sizeof(PACKET));
	}
}PACKET;
```

* To add Log for debugging

```bash
LOG_DEBUG("Error msg");		//print debug
LOG_ERROR("Error msg");		//print error
LOG_FATAL("Error msg");		//print fatal
LOG_INFO("Error msg");		//print info
```


Demo Play
-----------------
* Capture Images of Playing [demo](https://github.com/HYEONSEOK1/DAMBIEngine/tree/main/Test_Case) for dummy Client
<div align="center">
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/result1.PNG"><br><br>
  <img src="https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Resources/result2.PNG"><br><br>
</div>


Support
-----------------
[contributing.md](https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/Contributing.md)

Contact
-----------------
[E-mail Us!](simon365@naver.com)

License
-----------------
Dmabi Endine is licensed under [Apache License, Version 2.0.](https://github.com/HYEONSEOK1/DAMBIEngine/blob/main/LICENSE). By its terms, contributions submitted to the project are also done under that license.

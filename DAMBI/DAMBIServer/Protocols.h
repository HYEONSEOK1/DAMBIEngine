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

typedef struct message {
	int number;
	int age;
	char packet[10];
	message() { Init(); }
	void Init()
	{
		memset(this,0, sizeof(message));
	}
}message;
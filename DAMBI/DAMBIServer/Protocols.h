#pragma once
typedef enum CMD
{
	PACKET_SEND = 0x0001,
};

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
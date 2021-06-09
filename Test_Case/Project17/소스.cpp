#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<string>
#include<winsock2.h>
#include <vector>
typedef struct S_PACKET_HEADER
{
    USHORT   unCmd;
    UINT   unLen;
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
        memset(this, 0, sizeof(message));
    }
}message;
using namespace std;
void ShowErrorMessage(string message)
{
    cout << "[�����߻�]: " << message << '\n';
    system("pause");
    exit(1);
}

int main()
{
    WSADATA wsaData;
    SOCKET clientSocket;
    std::vector<SOCKET> list;
    SOCKADDR_IN serverAddress;
    int serverPort = 3587;
    char received[256];
    string sent;

    for (int i = 0; i < 300; i++)
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // Winsock���ʱ�ȭ�մϴ�.
            ShowErrorMessage("WSAStartup()");
        SOCKET clientSocket;
        clientSocket = socket(PF_INET, SOCK_STREAM, 0); // TCP �����������մϴ�.
        if (clientSocket == INVALID_SOCKET)
            ShowErrorMessage("socket()");
        memset(&serverAddress, 0, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // ���ڿ�IP����Ʈ��ũ����Ʈ��������
        serverAddress.sin_port = htons(serverPort); // 2����Ʈ������Ʈ��ũ����Ʈ��������

        if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
            ShowErrorMessage("connect()");
        cout << "[�������] connect()\n";
        list.push_back(clientSocket);
    }

    
    while (1) { // �ݺ������μ����θ޽����������ϰ��ڸ޽��������޹޽��ϴ�.
        for (int i = 0; i < 300; i++)
        {
            int len = sizeof(S_PACKET_HEADER);
            char* packet = new char[sizeof(S_PACKET_HEADER) + sizeof(message)];
            S_PACKET_HEADER header;
            header.unCmd = 1;
            header.unLen = (sizeof(message) + sizeof(S_PACKET_HEADER)) * 2;

            message msg;
            msg.age = 1;
            msg.number = 3;
            memcpy(msg.packet, "scs", 3);

            memcpy(packet, (char*)&header, sizeof(S_PACKET_HEADER));
            memcpy(packet + sizeof(S_PACKET_HEADER), (char*)&msg, sizeof(message));
            send(list[i], packet, (sizeof(S_PACKET_HEADER) + sizeof(message)) * 2, 0);
        }
    }
    closesocket(clientSocket);
    WSACleanup();
    system("pause");
    return 0;
}
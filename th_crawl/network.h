

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include <string>
using namespace std;

#pragma pack(push, 1)
typedef struct packet
{
	char str[1024];
}packet;
#pragma pack(pop)

class NetClient
{
private:
	bool ok;
	WSADATA wsData;
	SOCKADDR_IN serverAddress;
public:
	SOCKET Socket;
	bool StartUp();
	bool Connect(char *ip, int port);
	int GetData(char *buf, int bufSize);
	int SendData(packet data);
	int SendBuf(void *buf,int len);
	bool SendFile(const char* c, const char* name);
	void Close();
	void ErrorHandling(char* message);
};


void sendScore(const char *c, const char *file);
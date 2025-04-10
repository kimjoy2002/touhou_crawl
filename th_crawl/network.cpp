#include "network.h"
#include "replay.h"
#include "option_manager.h"
#include <winsock2.h>
#include <ws2tcpip.h>
bool is_little_endian()
{
	const int x = 1;
	if (*(char*)&x) {
		return true;
	}
	else {
		return false;
	}
}


void cccc(char *b, int s, char k)
{
	for(int i = 0; i < s; i++)
		b[i]^=k;
}



void sendScore(const char *c, const char *file)
{
	if (option_mg.getServerIp().empty())
		return;

	NetClient client;
	client.StartUp();

	addrinfo hints = {}, *result = nullptr;
	hints.ai_family = AF_INET;        // IPv4
	hints.ai_socktype = SOCK_STREAM;  // TCP

	std::string serverIp = option_mg.getServerIp();
	std::string serverPort = std::to_string(option_mg.getServerPort());

	int res = getaddrinfo(serverIp.c_str(), serverPort.c_str(), &hints, &result);
	if (res != 0 || result == nullptr) {
		printf("getaddrinfo fail: %d\n", res);
		return;
	}

	// IP 주소 문자열로 변환
	char ipStr[INET_ADDRSTRLEN] = {0};
	sockaddr_in *addr = (sockaddr_in *)result->ai_addr;
	inet_ntop(AF_INET, &(addr->sin_addr), ipStr, INET_ADDRSTRLEN);

	// 연결 시도
	client.Connect(ipStr, option_mg.getServerPort());

	// 데이터 전송
	packet data;
	strcpy_s(data.str, sizeof(data.str), "hello world");
	data.str[11] = 0;

	//client.SendData(data);
	client.SendFile(c, file);
	client.Close();

	freeaddrinfo(result);
	return;
}


bool NetClient::StartUp()
{
	ok = false;
	if(WSAStartup(MAKEWORD(2, 2), &wsData)!=0)
	{
		ErrorHandling("WSAStartup() errer");
		return false;
	}
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket==INVALID_SOCKET)
	{
		ErrorHandling("socket() error");
		return false;
	}
	return true;
}
bool NetClient::Connect(char *ip, int port)
{
	ZeroMemory(&serverAddress, sizeof(serverAddress));
	NetClient::serverAddress.sin_family=AF_INET;
	NetClient::serverAddress.sin_port=htons(port);

	if (inet_pton(AF_INET, ip, &serverAddress.sin_addr) <= 0) {
		ErrorHandling("inet_pton() fail");
		ok = false;
		return false;
	}

	if(connect(Socket, (SOCKADDR *)&(serverAddress), sizeof(serverAddress))==SOCKET_ERROR)
	{
		ErrorHandling("connect() error");
		ok = false;
		return false;
	}
	else
	{
		ok = true;
		return true;
	}
}
int NetClient::GetData(char *buf, int bufSize)
{
	if(!ok)
		return 0;
	
	return recv(Socket, buf, bufSize, 0);
}
int NetClient::SendData(packet data)
{
	if(!ok)
		return 0;
	int result;

	result = send(Socket, (LPCSTR)&data,sizeof(packet), 0);	
	if(result == SOCKET_ERROR){
		ErrorHandling("send() error 1");
	}
	else if(result != sizeof(packet) ){
		ErrorHandling("send() error 2");
	}
	return result;
}

int NetClient::SendBuf(void *buf,int len)
{
    char *cbuf = (char*)buf;
    int trans = 0;
    int re = 0;
	cccc(cbuf,len,21);

    while(trans<len)
    {
        re =send(Socket,cbuf+trans,len-trans,0);
        if(re <0)
        {
            return -1;    
        }
        trans += re;
    }    
    return trans;
}

bool NetClient::SendFile(const char* c,const char* name)
{
	if(!ok)
		return 0;
	char fname[256],fname2[256];
	FILE *fp, *fp2;  
	memset(fname,0,256);
	sprintf_s(fname,256,name);
	memset(fname2,0,256);
	sprintf_s(fname2,256,"%s",ReplayClass.replay_string.c_str());


	std::wstring wfilename = ConvertUTF8ToUTF16(fname);
	std::wstring wfilename2 = ConvertUTF8ToUTF16(fname2);
	if(_wfopen_s(&fp, wfilename.c_str(), L"rb") != 0 || !fp){
        return false;  
	}
	if(_wfopen_s(&fp2, wfilename2.c_str(), L"rb") != 0 || !fp2){
        return false;  
	}
 
    int len = 0,len2=0;
	fseek(fp,0,SEEK_END);
    len = ftell(fp);
    fseek(fp,0,SEEK_SET);
	fseek(fp2,0,SEEK_END);
    len2 = ftell(fp2);
    fseek(fp2,0,SEEK_SET);
   
    char buf[1024];
    char fstring[256];
    char fsize[64], fsize2[64];
	memset(fstring,0,256);
	memset(fsize,0,64);
	memset(fsize2,0,64);
	strcpy_s(fname+strlen(fname), 1,"\0");
	strcpy_s(fname2+strlen(fname2), 1,"\0");
	sprintf_s(fstring,256,c);
	strcpy_s(fstring+strlen(fstring), 1,"\0");
	SendBuf(fstring,256);
	SendBuf(fname,256);
	sprintf_s(fsize, 64,"%d",len);
    SendBuf(fsize,64);
	

	SendBuf(fname2,256);
	sprintf_s(fsize2,64,"%d",len2);
    SendBuf(fsize2,64);



    while(len>1024)
    {
        fread(buf,1,1024,fp);
        if(SendBuf(buf,1024) == -1)
        {
            return false;
        }
        len -=1024;
    }
    if(len>0)
    {
        fread(buf,1,len,fp);
        SendBuf(buf,len);
    }

    while(len2>1024)
    {
        fread(buf,1,1024,fp2);
        if(SendBuf(buf,1024) == -1)
        {
            return false;
        }
        len2 -=1024;
    }
    if(len2>0)
    {
        fread(buf,1,len2,fp2);
        SendBuf(buf,len2);
    }
	fclose(fp);
	fclose(fp2);
    return true;
}
void NetClient::Close()
{
	if(!ok)
		return;
	closesocket(Socket);
	WSACleanup();
}


void NetClient::ErrorHandling(string message)
{
	//fputs(message, stderr);
	//fputc('\n', stderr);
	//exit(1);
}
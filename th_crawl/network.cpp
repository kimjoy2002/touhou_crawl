#include "network.h"
#include "replay.h"
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
	NetClient client;

	client.StartUp();
	//client.Connect("127.0.0.1",12345);
	client.Connect("175.194.18.134",12345);
	packet data;
	strcpy(data.str,"hello world"); 
	data.str[11] = 0;
	//client.SendData(data);
	client.SendFile(c, file);
	client.Close();
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
	NetClient::serverAddress.sin_addr.s_addr=inet_addr(ip);
	NetClient::serverAddress.sin_family=AF_INET;
	NetClient::serverAddress.sin_port=htons(port);
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
	fp = fopen(fname,"rb");
	fp2 = fopen(fname2,"rb");

	if(fp == 0 || fp2 == 0)
        return false;  
 
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
	//strcpy(fname,"이름없음-20160329-043601.txt");
	strcpy(fname+strlen(fname),"\0");
	strcpy(fname2+strlen(fname2),"\0");
	sprintf_s(fstring,256,c);
	strcpy(fstring+strlen(fstring),"\0");
	SendBuf(fstring,256);
	SendBuf(fname,256);
	sprintf(fsize,"%d",len);
    SendBuf(fsize,64);
	

	SendBuf(fname2,256);
	sprintf(fsize2,"%d",len2);
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


void NetClient::ErrorHandling(char* message)
{
	//fputs(message, stderr);
	//fputc('\n', stderr);
	//exit(1);
}
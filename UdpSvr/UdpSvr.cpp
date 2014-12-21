// UdpSvr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD wVersionRequested;
	wVersionRequested = MAKEWORD(2,2);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(7000);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char recvBuf[100];

	while(1)
	{
		memset(recvBuf, 0, 100);
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		printf("RECV： %s \n", recvBuf);
	}
	
	closesocket(sockSrv);
	WSACleanup();
	return 0;
}


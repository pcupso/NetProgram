// UdpClient.cpp : 定义控制台应用程序的入口点。
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

	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(7000);

	sendto(sockClient, "This is udp connet to server!",
		strlen("This is udp connet to server!")+1, 0,
		(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	closesocket(sockClient);
	WSACleanup();
	return 0;
}


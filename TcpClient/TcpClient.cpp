// TcpClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequest;
	WSADATA wsaData;
	wVersionRequest = MAKEWORD(2, 2);
	WSAStartup(wVersionRequest, &wsaData);

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {
		WSACleanup();
		return 1; 
	}

	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char recvBuf[100];
	memset(recvBuf, 0, 100);
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

	send(sockClient, "This is cda!", strlen("This is cda!")+1, 0);

	closesocket(sockClient);
	WSACleanup();

	return 0;
}


// TcpSvr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>


int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequest;
	WSADATA wsaData;
	int err;

	wVersionRequest = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequest, &wsaData);
	if(err != 0){
		return 0;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) 
	{
		WSACleanup();
		return 1; 
	}

	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	listen(sockSrv, 4);

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	while(1)
	{
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

		//Send to Client
		char sendBuf[100];
		memset(sendBuf, 0, 100);
		sprintf(sendBuf, "Welcome! your IP is %s", 
			inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf)+1,0);

		char recvBuf[100];
		memset(recvBuf, 0, 100);
		recv(sockConn, recvBuf, 100, 0);
		printf("RECV: %s\n", recvBuf);

		//Recv from Client
		closesocket(sockConn);
	}
	return 0;
}


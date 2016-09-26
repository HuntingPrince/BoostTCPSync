// BoostTCPAsyncServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Session.h"
#include "TCP_Server.h"

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io_service;
	TCP_Server server(io_service);
	io_service.run();

	std::cout << "네트워크 접속 종료" << std::endl;
	
	getchar();

	return 0;
}


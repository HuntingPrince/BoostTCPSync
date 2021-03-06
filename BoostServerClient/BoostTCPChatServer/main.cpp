// BoostTCPChatServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost\thread.hpp>
#include "ChattingServer.h"

const int MAX_SESSION_COUNT = 100;

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io_service;

	ChatServer server(io_service);
	server.Init(MAX_SESSION_COUNT);
	server.Start();

	io_service.run();

	std::cout << "네트웍 접속 종료" << std::endl;

	getchar();

	return 0;
}


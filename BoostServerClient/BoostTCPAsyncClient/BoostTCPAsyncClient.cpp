// BoostTCPAsyncClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TCP_Client.h"

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::
		address::from_string(SERVER_IP), PORT_NUMBER);

	TCP_Client client(io_service);
	client.Connect(endpoint);
	io_service.run();
	std::cout << "네트워크 접속 종료" << std::endl;
	getchar();

	return 0;
}


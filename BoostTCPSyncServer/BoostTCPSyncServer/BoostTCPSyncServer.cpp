// BoostTCPSyncServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io_service;

	return 0;
}


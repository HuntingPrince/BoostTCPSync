// BoostTCPAsyncServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Session.h"
#include "TCP_Server.h"

int _tmain(int argc, _TCHAR* argv[])
{
	boost::asio::io_service io_service;
	TCP_Server server(io_service);
	io_service.run();

	std::cout << "��Ʈ��ũ ���� ����" << std::endl;
	
	getchar();

	return 0;
}


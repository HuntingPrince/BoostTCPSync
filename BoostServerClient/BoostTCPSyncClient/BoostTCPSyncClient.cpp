// BoostTCPSyncClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

/*
Boost TCP Server

*/

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

int _tmain(int argc, _TCHAR* argv[])
{
	// OS �� IO �� ���ִ� ģ��
	boost::asio::io_service io_service;

	// ���ӹ��� IP �� PORT ����
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER );

	// ���� ���� ���� �� ����
	boost::system::error_code connect_error;
	boost::asio::ip::tcp::socket socket(io_service);
	socket.connect(endpoint, connect_error);

	// ���� ���� ���� ó�� 
	if (connect_error)
	{
		std::cout << "���� ����. Error No. : " << connect_error.value() << ", Message : " << connect_error.message() << std::endl;
		getchar();
		return 0;
	}
	else
	{
		std::cout << "������ ���� ����" << std::endl;
	}

	// 7�� ������ �޼��� ������.
	for (int i = 0; i < 7; ++i)
	{
		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "%d - Send Message", i);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		// ������ �޼��� ������.
		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen));

		// 
		std::cout << "������ ���� �޼��� : " << szMessage << std::endl;

		// �����κ��� ���� �޼��� ���� ����
		std::array<char, 128> buf;
		buf.assign(0);

		// �����κ��� ����� �޼��� �ޱ�
		boost::system::error_code error;
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				std::cout << "������ ������ ���������ϴ�." << std::endl;
			}
			else
			{
				std::cout << "Error No. : " << error.value() << " error Message : " << error.message().c_str()
					<< std::endl;
			}
			break;
		}

		// 
		std::cout << "�������� ���� �޼��� : " << &buf[0] << std::endl;
	}

	if (socket.is_open())
	{
		socket.close();
	}

	getchar();

	return 0;
}

 
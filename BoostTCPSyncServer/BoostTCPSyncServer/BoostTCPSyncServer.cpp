// BoostTCPSyncServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	// OS 와 IO 를 해주는 친구
	boost::asio::io_service io_service;

	// 접속받을 IP 와 PORT 설정
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER);

	// Accept 할 acceptor 설정
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

	// 소켓의 Accept, read, write 등의 OS 와 통신할 io_service 세팅
	boost::asio::ip::tcp::socket socket(io_service);

	acceptor.accept(socket);

	std::cout << "클라이언트 접속" << std::endl;

	while(true)
	{
		// 데이터 버퍼 크기 지정
		std::array<char, 128> buf;
		buf.assign(0);

		boost::system::error_code error;

		// 클라이언트 접속 이후 클라이언트에서 요청하는 패킷 받는다.
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				std::cout << "클라이언트 연결이 끊어졌습니다." << std::endl;
			}
			else
			{
				std::cout << "Error No : " << error.value() << " error Message : " << error.message() << std::endl;
			}

			break;
		}
		
		std::cout << "클라이언트에서 받은 메세지 : " << &buf[0] << std::endl;

		// 받은 메세지 복사
		char szMessage[128] = {0,};
		sprintf_s( szMessage, 128 - 1, "Re : %s", &buf[0] );
		int nMsgLen = strnlen_s( szMessage, 128-1 );

		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen), ignored_error);
		std::cout << "클라이언트에 보낸 메세지 : " << szMessage << std::endl;
	}

	getchar();

	return 0;
}


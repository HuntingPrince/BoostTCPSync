// BoostTCPSyncClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER );

	// 소켓 에러 받을 것 설정
	boost::system::error_code connect_error;
	boost::asio::ip::tcp::socket socket(io_service);
	socket.connect(endpoint, connect_error);

	// 동기 연결 이후 처리 
	if (connect_error)
	{
		std::cout << "연결 실패. Error No. : " << connect_error.value() << ", Message : " << connect_error.message() << std::endl;
		getchar();
		return 0;
	}
	else
	{
		std::cout << "서버에 연결 성공" << std::endl;
	}

	// 7번 서버에 메세지 보낸다.
	for (int i = 0; i < 7; ++i)
	{
		char szMessage[128] = { 0, };
		sprintf_s(szMessage, 128 - 1, "%d - Send Message", i);
		int nMsgLen = strnlen_s(szMessage, 128 - 1);

		// 서버에 메세지 보낸다.
		boost::system::error_code ignored_error;
		socket.write_some(boost::asio::buffer(szMessage, nMsgLen));

		// 
		std::cout << "서버에 보낸 메세지 : " << szMessage << std::endl;

		// 서버로부터 받을 메세지 버퍼 설정
		std::array<char, 128> buf;
		buf.assign(0);

		// 서버로부터 동기로 메세지 받기
		boost::system::error_code error;
		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error)
		{
			if (error == boost::asio::error::eof)
			{
				std::cout << "서버와 연결이 끊어졌습니다." << std::endl;
			}
			else
			{
				std::cout << "Error No. : " << error.value() << " error Message : " << error.message().c_str()
					<< std::endl;
			}
			break;
		}

		// 
		std::cout << "서버에서 받은 메세지 : " << &buf[0] << std::endl;
	}

	if (socket.is_open())
	{
		socket.close();
	}

	getchar();

	return 0;
}

 
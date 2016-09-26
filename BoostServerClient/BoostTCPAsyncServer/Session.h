#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>


class Session
{
	// 멤버 변수
public:
	boost::asio::ip::tcp::socket m_Socket;		// 소켓
	std::string m_WriteMessage;					// Write Message
	std::array<char, 128> m_ReceiveBuffer;		// 클라 -> 서버 데이터 Receive 버퍼
	
public:
	void Session::PostReceive();
	void Session::handle_write(const boost::system::error_code& error, size_t bytes_transferred);
	void Session::handle_receive(const boost::system::error_code& error, size_t bytes_transferred);
	boost::asio::ip::tcp::socket& Socket()
	{
		return m_Socket;
	}

	// 생성자 소멸자.
public:
	Session(boost::asio::io_service& io_service);
	~Session();
};


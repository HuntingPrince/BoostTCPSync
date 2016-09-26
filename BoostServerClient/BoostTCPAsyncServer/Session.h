#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <list>


class Session
{
	// ��� ����
public:
	boost::asio::ip::tcp::socket m_Socket;		// ����
	std::string m_WriteMessage;					// Write Message
	std::array<char, 128> m_ReceiveBuffer;		// Ŭ�� -> ���� ������ Receive ����
	
public:
	void Session::PostReceive();
	void Session::handle_write(const boost::system::error_code& error, size_t bytes_transferred);
	void Session::handle_receive(const boost::system::error_code& error, size_t bytes_transferred);
	boost::asio::ip::tcp::socket& Socket()
	{
		return m_Socket;
	}

	// ������ �Ҹ���.
public:
	Session(boost::asio::io_service& io_service);
	~Session();
};


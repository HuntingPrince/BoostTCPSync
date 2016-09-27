#pragma once


#include <SDKDDKVer.h>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

class TCP_Client
{
public:
	boost::asio::io_service& m_io_service;
	boost::asio::ip::tcp::socket m_Socket;
	int m_nSeqNumber;
	std::array<char, 128> m_ReceiveBuffer;
	std::string m_WriteMessage;

public:
	void Connect(boost::asio::ip::tcp::endpoint& endpoint);
	void PostWrite();
	void PostReceive();
	void handle_connect(const boost::system::error_code& error);
	void handle_write(const boost::system::error_code& /*error*/, size_t
		/*bytes_transferred*/);
	void handle_receive(const boost::system::error_code& error, size_t
		bytes_transferred);
public:
	TCP_Client(boost::asio::io_service& io_service);
	~TCP_Client();
};


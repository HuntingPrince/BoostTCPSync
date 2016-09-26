#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <list>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "Session.h"

const unsigned short PORT_NUMBER = 31400;

class TCP_Server
{
public:
	int m_nSeqNumber;
	boost::asio::ip::tcp::acceptor m_acceptor;
	Session* m_pSession;

	void StartAccept();
	void handle_accept(Session* pSession, const boost::system::error_code& error);
public:
	TCP_Server(boost::asio::io_service& io_service);
	~TCP_Server();
};


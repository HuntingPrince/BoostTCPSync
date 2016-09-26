#include "stdafx.h"
#include "TCP_Server.h"



TCP_Server::TCP_Server(boost::asio::io_service& io_service)
: m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER) )
{
	m_pSession = nullptr;
	StartAccept();
}

TCP_Server::~TCP_Server()
{
	
	if (m_pSession != nullptr)
	{
		delete m_pSession;
	}
}

void TCP_Server::StartAccept()
{
	std::cout << "클라이언트 접속 대기....." << std::endl;

	m_pSession = new Session(m_acceptor.get_io_service());
	
	m_acceptor.async_accept
	(
		m_pSession->Socket(),
		boost::bind(&TCP_Server::handle_accept, this, m_pSession, boost::asio::placeholders::error)
	);
}

void TCP_Server::handle_accept(Session* pSession, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "클라이언트 접속 성공" << std::endl;

		pSession->PostReceive();
	}
}
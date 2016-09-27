#include "stdafx.h"
#include "TCP_Client.h"


TCP_Client::TCP_Client(boost::asio::io_service& io_service)
: m_io_service(io_service),
m_Socket(io_service),
m_nSeqNumber(0)
{

}

TCP_Client::~TCP_Client()
{
}

void TCP_Client::Connect(boost::asio::ip::tcp::endpoint& endpoint)
{
	m_Socket.async_connect
	(
		endpoint,
		boost::bind(&TCP_Client::handle_connect,
		this,
		boost::asio::placeholders::error)
	);
}


void TCP_Client::PostWrite()
{
	if (m_Socket.is_open() == false)
	{
		return;
	}
	if (m_nSeqNumber > 7)
	{
		m_Socket.close();
		return;
	}
	++m_nSeqNumber;
	char szMessage[128] = { 0, };
	sprintf_s(szMessage, 128 - 1, "%d - Send Message", m_nSeqNumber);

	m_WriteMessage = szMessage;
	boost::asio::async_write
	(
		m_Socket, boost::asio::buffer(m_WriteMessage),
		boost::bind(&TCP_Client::handle_write, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
	);
	
	PostReceive();
}


void TCP_Client::PostReceive()
{
	memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));
	m_Socket.async_read_some
	(
		boost::asio::buffer(m_ReceiveBuffer),
		boost::bind(&TCP_Client::handle_receive, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
	);

}
void TCP_Client::handle_connect(const boost::system::error_code& error)
{
	if (error)
	{
		std::cout << "connect failed : " << error.message() << std::endl;
	}
	else
	{
		std::cout << "connected" << std::endl;
		PostWrite();
	}
}

void TCP_Client::handle_write(const boost::system::error_code& /*error*/, size_t
	/*bytes_transferred*/)
{
}

void TCP_Client::handle_receive(const boost::system::error_code& error, size_t
	bytes_transferred)
{
	if (error)
	{
		if (error == boost::asio::error::eof)
		{
			std::cout << "서버와 연결이 끊어졌습니다" << std::endl;
		}
		else
		{
			std::cout << "error No: " << error.value() << " error Message: "
				<< error.message() << std::endl;
		}
	}
	else
	{
		const std::string strRecvMessage = m_ReceiveBuffer.data();
		std::cout << "서버에서 받은 메시지: " << strRecvMessage
			<< ", 받은 크기: " << bytes_transferred << std::endl;
		PostWrite();
	}
}

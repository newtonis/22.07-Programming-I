#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>


using namespace std;

class client {
	public:
		client();
		void startConnection(const char* host);
		void receiveMessage();
		~client();

	private:
		boost::asio::io_service* IO_handler;
		boost::asio::ip::tcp::socket* socket_forClient;
		boost::asio::ip::tcp::resolver* client_resolver;
		boost::asio::ip::tcp::resolver::iterator endpoint;
};

#endif

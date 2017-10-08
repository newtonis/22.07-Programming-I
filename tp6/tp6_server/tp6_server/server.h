#define _WIN32_WINNT 0x0501

#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"



class server {
	public:
		server();
		void start_to_listen();

		void sendMessage(char *buf,int size);
		void wait_for_message(char *ans, int *sz);
		void close_connection();

		void writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes);
		~server();

	private:
		boost::asio::io_service*  IO_handler;
		boost::asio::ip::tcp::socket* socket_forServer;
		boost::asio::ip::tcp::acceptor* server_acceptor;
};


#endif
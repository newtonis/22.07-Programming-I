
#include <iostream>
#include <cstdio>
#include <cstring>
#include "server.h"

using namespace std;


#define HELLO_PORT 50013


void server::writeCompletitionCallback(const boost::system::error_code& error, std::size_t transfered_bytes) {
	std::cout << std::endl << "Write Callback called" << std::endl;
}

void server::start_to_listen() {
	server_acceptor->accept(*socket_forServer);
	socket_forServer->non_blocking(true);
}

void server::sendMessage(char *buf, int size) {

	size_t len;
	boost::system::error_code error;

	do{
		len = socket_forServer->write_some(boost::asio::buffer(buf, size), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}

server::server() {
	IO_handler = new boost::asio::io_service();
	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), HELLO_PORT));
	std::cout << std::endl << "Ready. Port " << HELLO_PORT << " created" << std::endl;
}

server::~server() {
	cout << "closing server \n";
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}
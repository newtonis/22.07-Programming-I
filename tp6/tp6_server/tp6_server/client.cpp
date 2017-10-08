#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp> 
#include "client.h"

#define CLIENT_PORT "50013"

client::client() {
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

client::~client() {
	cout << "closing client\n";
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client::startConnection(const char* host) {
	endpoint = client_resolver->resolve(
		boost::asio::ip::tcp::resolver::query(host, CLIENT_PORT));

	cout << "Trying to connect to " << host << " on port " << CLIENT_PORT << std::endl;
	try {
		boost::asio::connect(*socket_forClient, endpoint);
	}catch (const boost::exception const& e){
		cout << "error " << boost::diagnostic_information(e) << '\n';
	}
	socket_forClient->non_blocking(true);
}

void client::receiveMessage() {

	boost::system::error_code error;
	char buf[512];
	size_t len = 0;
	cout << "Receiving Message" << std::endl;
	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;
	do
	{
		len = socket_forClient->read_some(boost::asio::buffer(buf), error);

		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e9;
			pastTime = currentTime;
			cout << "Pasaron " << elapsedSeconds << " segundos." << endl;
		}

		if (!error)
			buf[len] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
		std::cout << std::endl << "Server said: " << buf << std::endl;
	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}
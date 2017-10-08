#include <iostream>
#include "server.h"
#include "client.h"
#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"

using namespace std;

void server_test() {
	cout << "starting server test \n";
	
	server my_server;

	getchar();
}

void client_test() {
	cout << "starting client test \n";

	client my_client;

	my_client.startConnection("localhost");
	cout << "called \n";
	getchar();
}

int main(char argc , char *argv[]) {
	if (argc == 2 && strcmp(argv[1],"client") == 0) {
		cout << "starting as client \n";

		client_test();
	}
	else if (argc == 2 && strcmp(argv[1], "server") == 0) {
		cout << "starting as server \n";

		server_test();
	}else {
		cout << "program is not server nor client, ending \n";
		
		return 1;
	}

	cout << "ending program \n";
}
#include <iostream>
#include "server.h"
#include "client.h"

#define _WIN32_WINNT 0x0501

#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"


using namespace std;

void server_test() {
	cout << "starting server test \n";
	
	

	cout << "waiting people to call us \n";
	while (1) {
		server my_server;

		my_server.start_to_listen();

		char ans[512];
		int sz;
		my_server.wait_for_message(ans,&sz);
		cout << "sombedy said " << ans << '\n';

	}

	//getchar();
}

void client_test() {
	cout << "starting client test \n";

	client my_client;

	my_client.startConnection("localhost");
	if (!my_client.success()) {
		cout << "failure to connect \n";
		return ;
	}
	char data[1000];
	int sz = 0;

	//my_client.receiveMessage(data,&sz,1000);
	cout << "enter msg : ";
	cin >> data;

	my_client.send_message(data, strlen(data) );
	

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
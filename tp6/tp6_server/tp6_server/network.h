#ifndef NETWORK_H
#define NETWORK_H

#include "client.h"
#include "server.h"

class network { // handles all server/client behaviours of the computer
	

	public:
		network();
		void wait_for_message(char *data,int *size); // block and wait for some computer to estabish connection and send sequence
		void send_message(char *data,char *address,char *port); /// send message to address

	private:
		
		client my_client;
		server my_server;

};

#endif
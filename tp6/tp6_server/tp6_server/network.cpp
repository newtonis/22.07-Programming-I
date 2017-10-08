#include "network.h"


network::network() {
	cout << "starting network object \n";

}

void network::wait_for_message(char *data, int *size) {
	cout << "blocking program , waiting for message ... \n";
}

void network::send_message(char *data, char *address, char *port) {
	cout << "sending " << data << " to " << address << " : " << port << '\n';

}
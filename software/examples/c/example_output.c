
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

int main() {
	// Create IP connection to brickd
	IPConnection ipcon;
	if(ipcon_create(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not create connection\n");
		exit(1);
	}

	// Create device object
	IO4 io;
	io4_create(&io, UID); 

	// Add device to IP connection
	if(ipcon_add_device(&ipcon, &io) < 0) {
		fprintf(stderr, "Could not connect to Bricklet\n");
		exit(1);
	}
	// Don't use device before it is added to a connection

	// Set pin 1 to output low
	io4_set_configuration(&io, 1 << 1, 'o', false);

	// Set pin 2 and 3 to output high
	io4_set_configuration(&io, (1 << 2) | (1 << 3), 'o', true);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon);
}

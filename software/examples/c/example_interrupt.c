
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for interrupts
void cb_interrupt(uint8_t interrupt_mask, uint8_t value_mask) {
	printf("Interrupt by: %d\n", interrupt_mask);
	printf("Value: %d\n", value_mask);
}

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

	// Enable interrupt on pin 0 
	io4_set_interrupt(&io, 1 << 0),

	// Register callback for interrupts
	io4_register_callback(&io, IO4_CALLBACK_INTERRUPT, cb_interrupt);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon);
}

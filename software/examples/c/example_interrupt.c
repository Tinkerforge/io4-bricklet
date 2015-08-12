#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_io4.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for interrupts
void cb_interrupt(uint8_t interrupt_mask, uint8_t value_mask, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Interrupt by: %d\n", interrupt_mask);
	printf("Value: %d\n", value_mask);
}

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	IO4 io4;
	io4_create(&io4, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Register callback for interrupts
	io4_register_callback(&io4,
	                      IO4_CALLBACK_INTERRUPT,
	                      (void *)cb_interrupt,
	                      NULL);

	// Enable interrupt on pin 0
	io4_set_interrupt(&io4, 1 << 0);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}

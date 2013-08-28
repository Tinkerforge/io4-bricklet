/* io4-bricklet
 * Copyright (C) 2012-2013 Matthias Bolte <matthias@tinkerforge.com>
 * Copyright (C) 2011-2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config.h: IO-4 Bricklet specific configuration
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib/drivers/board/sam3s/SAM3S.h"
#include "bricklib/drivers/pio/pio.h"
#include "brickletlib/bricklet_entry.h"

#include "io.h"

#define BRICKLET_FIRMWARE_VERSION_MAJOR 2
#define BRICKLET_FIRMWARE_VERSION_MINOR 0
#define BRICKLET_FIRMWARE_VERSION_REVISION 1

#define BRICKLET_HARDWARE_VERSION_MAJOR 1
#define BRICKLET_HARDWARE_VERSION_MINOR 1
#define BRICKLET_HARDWARE_VERSION_REVISION 0

#define BRICKLET_DEVICE_IDENTIFIER 29

#define INVOCATION_IN_BRICKLET_CODE
#define PIN0 (BS->pin1_ad)
#define PIN1 (BS->pin2_da)
#define PIN2 (BS->pin3_pwm)
#define PIN3 (BS->pin4_io)

#define NUM_PINS 4

typedef struct {
	Pin *pins[NUM_PINS];
	uint32_t last_value[NUM_PINS];
	uint32_t time[NUM_PINS];
	uint32_t time_remaining[NUM_PINS];
	uint8_t monoflop_callback_mask;
	uint8_t interrupt;
	uint32_t debounce_period;
	uint32_t counter;

	uint32_t edge_count[NUM_PINS];
	uint8_t edge_type[NUM_PINS];
	uint8_t edge_debounce[NUM_PINS];
	uint8_t edge_debounce_counter[NUM_PINS];
	uint8_t edge_last_state[NUM_PINS];
} BrickContext;

#endif

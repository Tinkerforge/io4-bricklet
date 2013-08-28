/* io4-bricklet
 * Copyright (C) 2012-2013 Matthias Bolte <matthias@tinkerforge.com>
 * Copyright (C) 2011-2013 Olaf Lüke <olaf@tinkerforge.com>
 *
 * io.h: Implementation of IO-4 Bricklet messages
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

#ifndef IO4_H
#define IO4_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

#define EDGE_TYPE_RISING  0
#define EDGE_TYPE_FALLING 1
#define EDGE_TYPE_BOTH    2

#define FID_SET_VALUE 1
#define FID_GET_VALUE 2
#define FID_SET_CONFIGURATION 3
#define FID_GET_CONFIGURATION 4
#define FID_SET_DEBOUNCE_PERIOD 5
#define FID_GET_DEBOUNCE_PERIOD 6
#define FID_SET_INTERRUPT 7
#define FID_GET_INTERRUPT 8
#define FID_INTERRUPT 9
#define FID_SET_MONOFLOP 10
#define FID_GET_MONOFLOP 11
#define FID_MONOFLOP_DONE 12
#define FID_SET_SELECTED_VALUES 13
#define FID_GET_EDGE_COUNT 14
#define FID_SET_EDGE_COUNT_CONFIG 15
#define FID_GET_EDGE_COUNT_CONFIG 16

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetValue;

typedef struct {
	MessageHeader header;
	uint8_t value_mask;
} __attribute__((__packed__)) GetValueReturn;

typedef struct {
	MessageHeader header;
	uint8_t value_mask;
} __attribute__((__packed__)) SetValue;

typedef struct {
	MessageHeader header;
	uint8_t selection_mask;
	char direction;
	bool value;
} __attribute__((__packed__)) SetConfiguration;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetConfiguration;

typedef struct {
	MessageHeader header;
	uint8_t direction_mask;
	uint8_t value_mask;
} __attribute__((__packed__)) GetConfigurationReturn;

typedef struct {
	MessageHeader header;
	uint32_t debounce;
} __attribute__((__packed__)) SetDebouncePeriod;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetDebouncePeriod;

typedef struct {
	MessageHeader header;
	uint32_t debounce;
} __attribute__((__packed__)) GetDebouncePeriodReturn;

typedef struct {
	MessageHeader header;
	uint8_t interrupt_mask;
} __attribute__((__packed__)) SetInterrupt;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetInterrupt;

typedef struct {
	MessageHeader header;
	uint8_t interrupt_mask;
} __attribute__((__packed__)) GetInterruptReturn;

typedef struct {
	MessageHeader header;
	uint8_t interrupt_mask;
	uint8_t value_mask;
} __attribute__((__packed__)) InterruptSignal;

typedef struct {
	MessageHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
	uint32_t time;
} __attribute__((__packed__)) SetMonoflop;

typedef struct {
	MessageHeader header;
	uint8_t pin;
} __attribute__((__packed__)) GetMonoflop;

typedef struct {
	MessageHeader header;
	uint8_t value;
	uint32_t time;
	uint32_t time_remaining;
} __attribute__((__packed__)) GetMonoflopReturn;

typedef struct {
	MessageHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
} __attribute__((__packed__)) MonoflopDone;

typedef struct {
	MessageHeader header;
	uint8_t selection_mask;
	uint8_t value_mask;
} __attribute__((__packed__)) SetSelectedValues;

typedef struct {
	MessageHeader header;
	uint8_t pin;
	bool reset_counter;
} __attribute__((__packed__)) GetEdgeCount;

typedef struct {
	MessageHeader header;
	uint32_t count;
} __attribute__((__packed__)) GetEdgeCountReturn;

typedef struct {
	MessageHeader header;
	uint8_t selection_mask;
	uint8_t edge_type;
	uint8_t debounce;
} __attribute__((__packed__)) SetEdgeCountConfig;

typedef struct {
	MessageHeader header;
	uint8_t pin;
} __attribute__((__packed__)) GetEdgeCountConfig;

typedef struct {
	MessageHeader header;
	uint8_t edge_type;
	uint8_t debounce;
} __attribute__((__packed__)) GetEdgeCountConfigReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

void get_value(const ComType com, const GetValue *data);
void set_value(const ComType com, const SetValue *data);
void set_configuration(const ComType com, const SetConfiguration *data);
void get_configuration(const ComType com, const GetConfiguration *data);
void set_debounce_period(const ComType com, const SetDebouncePeriod *data);
void get_debounce_period(const ComType com, const GetDebouncePeriod *data);
void set_interrupt(const ComType com, const SetInterrupt *data);
void get_interrupt(const ComType com, const GetInterrupt *data);
void set_monoflop(const ComType com, const SetMonoflop *data);
void get_monoflop(const ComType com, const GetMonoflop *data);
void set_selected_values(const ComType com, const SetSelectedValues *data);
void get_edge_count(const ComType com, const GetEdgeCount *data);
void set_edge_count_config(const ComType com, const SetEdgeCountConfig *data);
void get_edge_count_config(const ComType com, const GetEdgeCountConfig *data);

void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif

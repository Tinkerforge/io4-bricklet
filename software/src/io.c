/* io4-bricklet
 * Copyright (C) 2012 Matthias Bolte <matthias@tinkerforge.com>
 * Copyright (C) 2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * io.c: Implementation of IO-4 Bricklet messages
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

#include "io.h"

#include "brickletlib/bricklet_entry.h"
#include "bricklib/utility/mutex.h"
#include "bricklib/utility/init.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "config.h"
#include <pio/pio_it.h>
#include <pio/pio.h>

const ComMessage com_messages[] = {
	{TYPE_SET_VALUE, (message_handler_func_t)set_value},
	{TYPE_GET_VALUE, (message_handler_func_t)get_value},
	{TYPE_SET_CONFIGURATION, (message_handler_func_t)set_configuration},
	{TYPE_GET_CONFIGURATION, (message_handler_func_t)get_configuration},
	{TYPE_SET_DEBOUNCE_PERIOD, (message_handler_func_t)set_debounce_period},
	{TYPE_GET_DEBOUNCE_PERIOD, (message_handler_func_t)get_debounce_period},
	{TYPE_SET_INTERRUPT, (message_handler_func_t)set_interrupt},
	{TYPE_GET_INTERRUPT, (message_handler_func_t)get_interrupt},
	{TYPE_INTERRUPT, (message_handler_func_t)NULL},
	{TYPE_SET_MONOFLOP, (message_handler_func_t)set_monoflop},
	{TYPE_GET_MONOFLOP, (message_handler_func_t)get_monoflop},
};

void invocation(uint8_t com, uint8_t *data) {
	uint8_t id = ((StandardMessage*)data)->type - 1;
	if(id < NUM_MESSAGES) {
		BRICKLET_OFFSET(com_messages[id].reply_func)(com, data);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	BC->pins[0] = &PIN0;
	BC->pins[1] = &PIN1;
	BC->pins[2] = &PIN2;
	BC->pins[3] = &PIN3;

	for(uint8_t i = 0; i < NUM_PINS; i++) {
		BC->pins[i]->type = PIO_INPUT;
		BC->pins[i]->attribute = PIO_PULLUP;
		BC->last_value[i] = BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask;
		BC->time[i] = 0;
		BC->time_remaining[i] = 0;
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);

	BC->monoflop_callback_mask = 0;
	BC->counter = 0;
	BC->interrupt = 0;
	BC->debounce_period = 100;
}

void destructor(void) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		BC->pins[i]->type = PIO_INPUT;
		BC->pins[i]->attribute = PIO_PULLUP;
	}
	BA->PIO_Configure(*BC->pins, NUM_PINS);
}

uint8_t make_value(void) {
	uint8_t value = 0;
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
			value |= (1 << i);
		}
	}

	return value;
}

void tick(uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->counter != 0) {
			BC->counter--;
		}

		uint8_t last_monoflop_callback_mask = BC->monoflop_callback_mask;

		for(uint8_t i = 0; i < NUM_PINS; i++) {
			if(BC->time_remaining[i] != 0) {
				BC->time_remaining[i]--;
				if(BC->time_remaining[i] == 0) {
					if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
						BC->pins[i]->type = PIO_OUTPUT_0;
					} else {
						BC->pins[i]->type = PIO_OUTPUT_1;
					}
					BC->monoflop_callback_mask |= (1 << i);
				}
			}
		}

		if(BC->monoflop_callback_mask != last_monoflop_callback_mask) {
			BA->PIO_Configure(*BC->pins, NUM_PINS);
		}
	}

	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->counter == 0) {
			uint8_t interrupt = 0;
			for(uint8_t i = 0; i < NUM_PINS; i++) {
				if(BC->interrupt & (1 << i)) {
					uint32_t value = BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask;
					if(value != BC->last_value[i]) {
						interrupt |= (1 << i);
						BC->last_value[i] = value;
					}
				}
			}
			if(interrupt != 0) {
				InterruptSignal is = {
					BS->stack_id,
					TYPE_INTERRUPT,
					sizeof(InterruptSignal),
					interrupt,
					make_value()
				};

				BA->send_blocking_with_timeout(&is,
				                               sizeof(InterruptSignal),
				                               *BA->com_current);
				BC->counter = BC->debounce_period;
			}
		}

		if(BC->monoflop_callback_mask) {
			MonoflopDone md = {
				BS->stack_id,
				TYPE_MONOFLOP_DONE,
				sizeof(MonoflopDone),
				0,
				0
			};

			for(uint8_t i = 0; i < NUM_PINS; i++) {
				if (BC->monoflop_callback_mask & (1 << i)) {
					md.pin_mask |= (1 << i);

					if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
						md.value_mask |= (1 << i);
					}
				}
			}

			BA->send_blocking_with_timeout(&md,
			                               sizeof(MonoflopDone),
			                               *BA->com_current);

			BC->monoflop_callback_mask = 0;
		}
	}
}

void get_value(uint8_t com, const GetValue *data) {
	GetValueReturn gvr;

	gvr.stack_id      = data->stack_id;
	gvr.type          = data->type;
	gvr.length        = sizeof(GetValueReturn);
	gvr.value_mask    = make_value();

	BA->send_blocking_with_timeout(&gvr, sizeof(GetValueReturn), com);
}

void set_value(uint8_t com, const SetValue *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i]->type != PIO_INPUT) {
			if(data->value_mask & (1 << i)) {
				BC->pins[i]->type = PIO_OUTPUT_1;
			} else {
				BC->pins[i]->type = PIO_OUTPUT_0;
			}
			BC->time_remaining[i] = 0;
		}
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);
}

void set_configuration(uint8_t com, const SetConfiguration *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(data->pin_mask & (1 << i)) {
			if(data->direction == 'i' || data->direction == 'I') {
				BC->pins[i]->type = PIO_INPUT;
				BC->time_remaining[i] = 0;
				if(data->value) {
					BC->pins[i]->attribute = PIO_PULLUP;
				} else {
					BC->pins[i]->attribute = PIO_DEFAULT;
				}
			} else if(data->direction == 'o' || data->direction == 'O') {
				BC->pins[i]->attribute = PIO_DEFAULT;
				BC->time_remaining[i] = 0;
				if(data->value) {
					BC->pins[i]->type = PIO_OUTPUT_1;
				} else {
					BC->pins[i]->type = PIO_OUTPUT_0;
				}
			}
		}
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);
}

void get_configuration(uint8_t com, const GetConfiguration *data) {
	uint8_t direction_mask = 0;
	uint8_t value_mask = 0;

	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i]->type == PIO_INPUT) {
			direction_mask |= (1 << i);
			if(BC->pins[i]->attribute == PIO_PULLUP) {
				value_mask |= (1 << i);
			}
		} else {
			if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
				value_mask |= (1 << i);
			}
		}
	}

	GetConfigurationReturn gcr;

	gcr.stack_id       = data->stack_id;
	gcr.type           = data->type;
	gcr.length         = sizeof(GetConfigurationReturn);
	gcr.direction_mask = direction_mask;
	gcr.value_mask     = value_mask;

	BA->send_blocking_with_timeout(&gcr, sizeof(GetConfigurationReturn), com);
}

void set_debounce_period(uint8_t com, const SetDebouncePeriod *data) {
	BC->debounce_period = data->debounce;
}

void get_debounce_period(uint8_t com, const GetDebouncePeriod *data) {
	GetDebouncePeriodReturn gdpr;

	gdpr.stack_id       = data->stack_id;
	gdpr.type           = data->type;
	gdpr.length         = sizeof(GetDebouncePeriodReturn);
	gdpr.debounce       = BC->debounce_period;

	BA->send_blocking_with_timeout(&gdpr, sizeof(GetDebouncePeriodReturn), com);
}

void set_interrupt(uint8_t com, const SetInterrupt *data) {
	BC->interrupt = data->interrupt_mask;
}

void get_interrupt(uint8_t com, const GetInterrupt *data) {
	GetInterruptReturn gir;

	gir.stack_id       = data->stack_id;
	gir.type           = data->type;
	gir.length         = sizeof(GetInterruptReturn);
	gir.interrupt_mask = BC->interrupt;

	BA->send_blocking_with_timeout(&gir, sizeof(GetInterruptReturn), com);
}

void set_monoflop(uint8_t com, SetMonoflop *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if((data->pin_mask & (1 << i)) && BC->pins[i]->type != PIO_INPUT) {
			if(data->value_mask & (1 << i)) {
				BC->pins[i]->type = PIO_OUTPUT_1;
			} else {
				BC->pins[i]->type = PIO_OUTPUT_0;
			}

			BC->time[i] = data->time;
			BC->time_remaining[i] = data->time;
		}
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);
}

void get_monoflop(uint8_t com, GetMonoflop *data) {
	if(data->pin >= NUM_PINS) {
		// TODO: Error?
		return;
	}

	GetMonoflopReturn gmr;

	gmr.stack_id       = data->stack_id;
	gmr.type           = data->type;
	gmr.length         = sizeof(GetMonoflopReturn);
	gmr.value          = (BC->pins[data->pin]->pio->PIO_PDSR & BC->pins[data->pin]->mask) ? 1 : 0;
	gmr.time           = BC->time[data->pin];
	gmr.time_remaining = BC->time_remaining[data->pin];

	BA->send_blocking_with_timeout(&gmr, sizeof(GetMonoflopReturn), com);
}

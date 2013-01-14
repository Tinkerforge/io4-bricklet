/* io4-bricklet
 * Copyright (C) 2012 Matthias Bolte <matthias@tinkerforge.com>
 * Copyright (C) 2011-2013 Olaf Lüke <olaf@tinkerforge.com>
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
#include "bricklib/drivers/pio/pio.h"
#include "config.h"

void invocation(const ComType com, const uint8_t *data) {
	switch(((MessageHeader*)data)->fid) {
		case FID_SET_VALUE: {
			set_value(com, (SetValue*)data);
			break;
		}

		case FID_GET_VALUE: {
			get_value(com, (GetValue*)data);
			break;
		}

		case FID_SET_CONFIGURATION: {
			set_configuration(com, (SetConfiguration*)data);
			break;
		}

		case FID_GET_CONFIGURATION: {
			get_configuration(com, (GetConfiguration*)data);
			break;
		}

		case FID_SET_DEBOUNCE_PERIOD: {
			set_debounce_period(com, (SetDebouncePeriod*)data);
			break;
		}

		case FID_GET_DEBOUNCE_PERIOD: {
			get_debounce_period(com, (GetDebouncePeriod*)data);
			break;
		}

		case FID_SET_INTERRUPT: {
			set_interrupt(com, (SetInterrupt*)data);
			break;
		}

		case FID_GET_INTERRUPT: {
			get_interrupt(com, (GetInterrupt*)data);
			break;
		}

		case FID_SET_MONOFLOP: {
			set_monoflop(com, (SetMonoflop*)data);
			break;
		}

		case FID_GET_MONOFLOP: {
			get_monoflop(com, (GetMonoflop*)data);
			break;
		}

		case FID_SET_SELECTED_VALUES: {
			set_selected_values(com, (SetSelectedValues*)data);
			break;
		}

		default: {
			BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_NOT_SUPPORTED, com);
			break;
		}
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
		BC->time[i] = 0;
		BC->time_remaining[i] = 0;
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		BC->last_value[i] = BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask;
	}

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

void tick(const uint8_t tick_type) {
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
				InterruptSignal is;
				BA->com_make_default_header(&is, BS->uid, sizeof(InterruptSignal), FID_INTERRUPT);
				is.interrupt_mask = interrupt;
				is.value_mask     = make_value();

				BA->send_blocking_with_timeout(&is,
				                               sizeof(InterruptSignal),
				                               *BA->com_current);
				BC->counter = BC->debounce_period;
			}
		}

		if(BC->monoflop_callback_mask) {
			MonoflopDone md;

			BA->com_make_default_header(&md, BS->uid, sizeof(MonoflopDone), FID_MONOFLOP_DONE);
			md.selection_mask = 0;
			md.value_mask     = 0;

			for(uint8_t i = 0; i < NUM_PINS; i++) {
				if (BC->monoflop_callback_mask & (1 << i)) {
					md.selection_mask |= (1 << i);

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

void get_value(const ComType com, const GetValue *data) {
	GetValueReturn gvr;

	gvr.header        = data->header;
	gvr.header.length = sizeof(GetValueReturn);
	gvr.value_mask    = make_value();

	BA->send_blocking_with_timeout(&gvr, sizeof(GetValueReturn), com);
}

void set_value(const ComType com, const SetValue *data) {
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
	BA->com_return_setter(com, data);
}

void set_configuration(const ComType com, const SetConfiguration *data) {
	if(data->direction != 'i' && data->direction != 'I' &&
	   data->direction != 'o' && data->direction != 'O') {
		BA->com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(data->selection_mask & (1 << i)) {
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
	BA->com_return_setter(com, data);
}

void get_configuration(const ComType com, const GetConfiguration *data) {
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

	gcr.header         = data->header;
	gcr.header.length  = sizeof(GetConfigurationReturn);
	gcr.direction_mask = direction_mask;
	gcr.value_mask     = value_mask;

	BA->send_blocking_with_timeout(&gcr, sizeof(GetConfigurationReturn), com);
}

void set_debounce_period(const ComType com, const SetDebouncePeriod *data) {
	BC->debounce_period = data->debounce;
	BA->com_return_setter(com, data);
}

void get_debounce_period(const ComType com, const GetDebouncePeriod *data) {
	GetDebouncePeriodReturn gdpr;

	gdpr.header         = data->header;
	gdpr.header.length  = sizeof(GetDebouncePeriodReturn);
	gdpr.debounce       = BC->debounce_period;

	BA->send_blocking_with_timeout(&gdpr, sizeof(GetDebouncePeriodReturn), com);
}

void set_interrupt(const ComType com, const SetInterrupt *data) {
	BC->interrupt = data->interrupt_mask;
	BA->com_return_setter(com, data);
}

void get_interrupt(const ComType com, const GetInterrupt *data) {
	GetInterruptReturn gir;

	gir.header         = data->header;
	gir.header.length  = sizeof(GetInterruptReturn);
	gir.interrupt_mask = BC->interrupt;

	BA->send_blocking_with_timeout(&gir, sizeof(GetInterruptReturn), com);
}

void set_monoflop(const ComType com, const SetMonoflop *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if((data->selection_mask & (1 << i)) && BC->pins[i]->type != PIO_INPUT) {
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
	BA->com_return_setter(com, data);
}

void get_monoflop(const ComType com, const GetMonoflop *data) {
	if(data->pin >= NUM_PINS) {
		BA->com_return_error(data, sizeof(GetMonoflopReturn), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	GetMonoflopReturn gmr;

	gmr.header         = data->header;
	gmr.header.length  = sizeof(GetMonoflopReturn);
	gmr.value          = (BC->pins[data->pin]->pio->PIO_PDSR & BC->pins[data->pin]->mask) ? 1 : 0;
	gmr.time           = BC->time[data->pin];
	gmr.time_remaining = BC->time_remaining[data->pin];

	BA->send_blocking_with_timeout(&gmr, sizeof(GetMonoflopReturn), com);
}

void set_selected_values(const ComType com, const SetSelectedValues *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(data->selection_mask & (1 << i)) {
			if(BC->pins[i]->type != PIO_INPUT) {
				if(data->value_mask & (1 << i)) {
					BC->pins[i]->type = PIO_OUTPUT_1;
				} else {
					BC->pins[i]->type = PIO_OUTPUT_0;
				}
				BC->time_remaining[i] = 0;
			}
		}
	}

	BA->PIO_Configure(*BC->pins, NUM_PINS);
	BA->com_return_setter(com, data);

}

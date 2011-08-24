/*************************************************************
 * This file was automatically generated on 2011-08-23.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#include "bricklet_io4.h"

#include <string.h>

#define TYPE_SET_VALUE 1
#define TYPE_GET_VALUE 2
#define TYPE_SET_CONFIGURATION 3
#define TYPE_GET_CONFIGURATION 4
#define TYPE_SET_DEBOUNCE_PERIOD 5
#define TYPE_GET_DEBOUNCE_PERIOD 6
#define TYPE_SET_INTERRUPT 7
#define TYPE_GET_INTERRUPT 8
#define TYPE_INTERRUPT 9

typedef void (*interrupt_func_t)(uint8_t, uint8_t);

#ifdef _MSC_VER
	#pragma pack(push)
	#pragma pack(1)

	#define PACKED
#else
	#define PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t value_mask;
} PACKED SetValue;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetValue;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t value_mask;
} PACKED GetValueReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t pin_mask;
	char direction;
	bool value;
} PACKED SetConfiguration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetConfiguration;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t direction_mask;
	uint8_t value_mask;
} PACKED GetConfigurationReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint32_t debounce;
} PACKED SetDebouncePeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetDebouncePeriod;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint32_t debounce;
} PACKED GetDebouncePeriodReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t interrupt_mask;
} PACKED SetInterrupt;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetInterrupt;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t interrupt_mask;
} PACKED GetInterruptReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t interrupt_mask;
	uint8_t value_mask;
} PACKED InterruptCallback;

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

int io4_set_value(IO4 *io4, uint8_t value_mask) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	SetValue sv;
	sv.stack_id = io4->stack_id;
	sv.type = TYPE_SET_VALUE;
	sv.length = sizeof(SetValue);
	sv.value_mask = value_mask;

	ipcon_device_write(io4, (char *)&sv, sizeof(SetValue));

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_get_value(IO4 *io4, uint8_t *ret_value_mask) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	io4->answer.type = TYPE_GET_VALUE;
	io4->answer.length = sizeof(GetValueReturn);
	GetValue gv;
	gv.stack_id = io4->stack_id;
	gv.type = TYPE_GET_VALUE;
	gv.length = sizeof(GetValue);

	ipcon_device_write(io4, (char *)&gv, sizeof(GetValue));

	if(ipcon_answer_sem_wait_timeout(io4) != 0) {
		ipcon_sem_post_write(io4);
		return E_TIMEOUT;
	}

	GetValueReturn *gvr = (GetValueReturn *)io4->answer.buffer;
	*ret_value_mask = gvr->value_mask;

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_set_configuration(IO4 *io4, uint8_t pin_mask, char direction, bool value) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	SetConfiguration sc;
	sc.stack_id = io4->stack_id;
	sc.type = TYPE_SET_CONFIGURATION;
	sc.length = sizeof(SetConfiguration);
	sc.pin_mask = pin_mask;
	sc.direction = direction;
	sc.value = value;

	ipcon_device_write(io4, (char *)&sc, sizeof(SetConfiguration));

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_get_configuration(IO4 *io4, uint8_t *ret_direction_mask, uint8_t *ret_value_mask) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	io4->answer.type = TYPE_GET_CONFIGURATION;
	io4->answer.length = sizeof(GetConfigurationReturn);
	GetConfiguration gc;
	gc.stack_id = io4->stack_id;
	gc.type = TYPE_GET_CONFIGURATION;
	gc.length = sizeof(GetConfiguration);

	ipcon_device_write(io4, (char *)&gc, sizeof(GetConfiguration));

	if(ipcon_answer_sem_wait_timeout(io4) != 0) {
		ipcon_sem_post_write(io4);
		return E_TIMEOUT;
	}

	GetConfigurationReturn *gcr = (GetConfigurationReturn *)io4->answer.buffer;
	*ret_direction_mask = gcr->direction_mask;
	*ret_value_mask = gcr->value_mask;

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_set_debounce_period(IO4 *io4, uint32_t debounce) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	SetDebouncePeriod sdp;
	sdp.stack_id = io4->stack_id;
	sdp.type = TYPE_SET_DEBOUNCE_PERIOD;
	sdp.length = sizeof(SetDebouncePeriod);
	sdp.debounce = debounce;

	ipcon_device_write(io4, (char *)&sdp, sizeof(SetDebouncePeriod));

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_get_debounce_period(IO4 *io4, uint32_t *ret_debounce) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	io4->answer.type = TYPE_GET_DEBOUNCE_PERIOD;
	io4->answer.length = sizeof(GetDebouncePeriodReturn);
	GetDebouncePeriod gdp;
	gdp.stack_id = io4->stack_id;
	gdp.type = TYPE_GET_DEBOUNCE_PERIOD;
	gdp.length = sizeof(GetDebouncePeriod);

	ipcon_device_write(io4, (char *)&gdp, sizeof(GetDebouncePeriod));

	if(ipcon_answer_sem_wait_timeout(io4) != 0) {
		ipcon_sem_post_write(io4);
		return E_TIMEOUT;
	}

	GetDebouncePeriodReturn *gdpr = (GetDebouncePeriodReturn *)io4->answer.buffer;
	*ret_debounce = gdpr->debounce;

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_set_interrupt(IO4 *io4, uint8_t interrupt_mask) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	SetInterrupt si;
	si.stack_id = io4->stack_id;
	si.type = TYPE_SET_INTERRUPT;
	si.length = sizeof(SetInterrupt);
	si.interrupt_mask = interrupt_mask;

	ipcon_device_write(io4, (char *)&si, sizeof(SetInterrupt));

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_get_interrupt(IO4 *io4, uint8_t *ret_interrupt_mask) {
	if(io4->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(io4);

	io4->answer.type = TYPE_GET_INTERRUPT;
	io4->answer.length = sizeof(GetInterruptReturn);
	GetInterrupt gi;
	gi.stack_id = io4->stack_id;
	gi.type = TYPE_GET_INTERRUPT;
	gi.length = sizeof(GetInterrupt);

	ipcon_device_write(io4, (char *)&gi, sizeof(GetInterrupt));

	if(ipcon_answer_sem_wait_timeout(io4) != 0) {
		ipcon_sem_post_write(io4);
		return E_TIMEOUT;
	}

	GetInterruptReturn *gir = (GetInterruptReturn *)io4->answer.buffer;
	*ret_interrupt_mask = gir->interrupt_mask;

	ipcon_sem_post_write(io4);

	return E_OK;
}

int io4_callback_interrupt(IO4 *io4, const unsigned char *buffer) {
	InterruptCallback *ic = (InterruptCallback *)buffer;
	((interrupt_func_t)io4->callbacks[ic->type])(ic->interrupt_mask, ic->value_mask);
	return sizeof(InterruptCallback);
}

void io4_register_callback(IO4 *io4, uint8_t cb, void *func) {
    io4->callbacks[cb] = func;
}

void io4_create(IO4 *io4, const char *uid) {
	ipcon_device_create(io4, uid);

	io4->device_callbacks[TYPE_INTERRUPT] = io4_callback_interrupt;
}

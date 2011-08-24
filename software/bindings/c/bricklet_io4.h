/*************************************************************
 * This file was automatically generated on 23.08.2011.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICKLET_IO4_H
#define BRICKLET_IO4_H

#include "ip_connection.h"

typedef Device IO4;

#define IO4_CALLBACK_INTERRUPT 9

void io4_create(IO4 *io4, const char *uid);

int io4_set_value(IO4 *io4, uint8_t value_mask);
int io4_get_value(IO4 *io4, uint8_t *ret_value_mask);
int io4_set_configuration(IO4 *io4, uint8_t pin_mask, char direction, bool value);
int io4_get_configuration(IO4 *io4, uint8_t *ret_direction_mask, uint8_t *ret_value_mask);
int io4_set_debounce_period(IO4 *io4, uint32_t debounce);
int io4_get_debounce_period(IO4 *io4, uint32_t *ret_debounce);
int io4_set_interrupt(IO4 *io4, uint8_t interrupt_mask);
int io4_get_interrupt(IO4 *io4, uint8_t *ret_interrupt_mask);
int io4_interrupt(IO4 *io4, uint8_t *ret_interrupt_mask, uint8_t *ret_value_mask);

void io4_register_callback(IO4 *io4, uint8_t cb, void *func);

#endif
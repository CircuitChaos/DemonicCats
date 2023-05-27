#pragma once

#include <avr/io.h>
#include <stdbool.h>

/* Pin assignments:
 * pin	function	state	port	ddr
 * ------------------------------------
 * pb7	n/a			float	0		0
 * pb6	n/a			float	0		0
 * pb5	reset		pullup	1		0
 * pb4	led2		low		0		1
 * pb3	led1		low		0		1
 * pb2	lx			float	0		0
 * pb1	n/c			pullup	1		0
 * pb0	n/c			pullup	1		0
 */

/* ADC1 */
#define IO_LX_ADMUX	_BV(MUX0)

static inline void io_init()
{
	PORTB	= 0b00100011;
	DDRB	= 0b00011000;
	DIDR0	= _BV(ADC1D);
}

static inline void io_led_set(bool which, bool state)
{
	const uint8_t mask = _BV(which ? 4 : 3);
	if(state)
		PORTB |= mask;
	else
		PORTB &= ~mask;
}

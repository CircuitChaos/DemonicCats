#include <avr/io.h>
#include "lx.h"
#include "io.h"

void lx_start(void)
{
	/* - Reference voltage: Vcc
	 * - ADLAR enabled (use only ADCH with 8-bit resolution)
	 * - Input: as in IO
	 */
	ADMUX	= _BV(ADLAR) | IO_LX_ADMUX;

	/* - ADC Enabled
	 * - Start conversion immediately
	 * - Prescale by 2 (64 kHz ADC clock)
	 */
	ADCSRA	= _BV(ADEN) | _BV(ADSC);

	/* Multiplexer disabled, free-running mode (not used because ADATE not set */
	ADCSRB	= 0;
}

lx_status_t lx_get(void)
{
	uint8_t value;

	if(!(ADCSRA & _BV(ADIF)))
		return LX_UNKNOWN;

	value = ADCH;
	ADCSRA |= _BV(ADIF);

	/* Assume light if > 1/4 Vcc */
	return (value > 64) ? LX_LIGHT : LX_DARK;
}

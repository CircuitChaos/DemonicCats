#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "blinking.h"
#include "io.h"
#include "lx.h"

static inline void enable_power_save(void)
{
	TCCR0B = _BV(CS02) | _BV(CS00);
}

static inline void disable_power_save(void)
{
	TCCR0B = _BV(CS01);
}

ISR(TIM0_OVF_vect)
{
	static bool running = false;

	wdt_reset();

	switch(lx_get()) {
		case LX_UNKNOWN:
			break;

		case LX_LIGHT:
			lx_start();
			if(running) {
				blinking_disable();
				enable_power_save();
				running = false;
			}
			break;

		case LX_DARK:
			lx_start();
			if(!running) {
				blinking_enable();
				disable_power_save();
				running = true;
			}
			break;
	}

	if(running) {
		blinking_tick();
		TCNT0 = 185;
	}
}

int main(void)
{
	io_init();
	lx_start();
	wdt_enable(WDTO_8S);

	TCCR0A	= 0;
	TIMSK0	= _BV(TOIE0);
	enable_power_save();

	sei();

	set_sleep_mode(SLEEP_MODE_IDLE);
	for(;;)
		sleep_mode();

	/* NOTREACHED */
	return 0;
}

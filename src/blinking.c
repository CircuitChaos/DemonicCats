#include <stdbool.h>
#include "blinking.h"
#include "io.h"

static bool enabled = false;
static uint16_t cnt;

void blinking_enable(void)
{
	enabled = true;
	cnt = 0;
}

void blinking_disable(void)
{
	enabled = false;
	io_led_set(false, false);
	io_led_set(true, false);
}

void blinking_tick(void)
{
	if(!enabled)
		return;

	const uint8_t pwm_counter = cnt & 0x0f;
	const uint8_t pwm_value = (cnt >> 5) & 0x0f;
	const uint8_t divider = (cnt >> 9) & 0x03;
	const bool which = (cnt >> 11) & 1;

	if(divider == 3) {
		if(pwm_counter > pwm_value)
			io_led_set(which,  true);
		else
			io_led_set(which, false);
	}

	++cnt;
}

#pragma once

typedef enum
{
	LX_UNKNOWN,	/* Unknown yet */
	LX_LIGHT,	/* LX pin is above threshold, need to stop */
	LX_DARK,	/* LX pin is below threshold, can continue */
} lx_status_t;

void lx_start(void);
lx_status_t lx_get(void);

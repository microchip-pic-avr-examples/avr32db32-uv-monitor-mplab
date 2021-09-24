#include "SLPCTRL.h"

#include <xc.h>

void initSleepControl(void)
{
    SLPCTRL.CTRLA = SLPCTRL_SMODE_STDBY_gc;
}
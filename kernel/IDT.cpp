#include "IDT.h"
#include "types.h"
#include "Screen.h"

extern "C" {

void isr_default_int(void)
{
}

void isr_clock_int(void)
{
	static int tic = 0;
	static int sec = 0;
	tic++;
	if (tic % 100 == 0) {
		sec++;
		tic = 0;
	}
}

void isr_kbd_int(void)
{
}

}

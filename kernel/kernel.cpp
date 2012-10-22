#include "Screen.h"
#include "GDT.h"

int main();

struct mb_partial_info;

extern "C" void kmain(struct mb_partial_info *k)
{
    memory::GDT gdt;

    gdt.commit();
	asm("movw $0x18, %ax \n \
        movw %ax, %ss \n \
        movl $0x20000, %esp");

    main();
}

int main()
{
	tty.attr(0x5E);
    tty.puts("un message\n");

	tty.attr(0x4E);
	tty.puts("un autre message\n");

	tty.scrollup(2);
	while (1);
}

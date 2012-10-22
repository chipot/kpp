#include "GDT.h"
#include "klib.h"

memory::gdtr gdt_reg{0, 0};

namespace memory {

void GDT::add_entry(u32 base, u32 offset, u8 acces, u8 other)
{
    gdt_entry *desc = &this->gdt[_last_offset++];

    desc->lim0_15   = (offset & 0xffff);
    desc->base0_15  = (base   & 0xffff);
    desc->base16_23 = (base   & 0xff0000) >> 16;
    desc->acces     = (acces);
    desc->lim16_19  = (offset & 0xf0000) >> 16;
    desc->other     = (other  & 0xf);
    desc->base24_31 = (base   & 0xff000000) >> 24;
    return;
}

GDT::GDT()
{
    this->gdt_ptr = &gdt_reg;
	/* initialisation des descripteurs de segment */
	add_entry(0x0, 0x0, 0x0, 0x0);
	add_entry(0x0, 0xFFFFF, 0x9B, 0x0D); /* code */
	add_entry(0x0, 0xFFFFF, 0x93, 0x0D); /* data */
	add_entry(0x0, 0x0, 0x97, 0x0D);		/* stack */

	/* initialisation de la structure pour GDTR */
	gdt_ptr->limite = GDTSIZE * 8;
	gdt_ptr->base = GDTBASE;
}

void GDT::commit()
{
	/* recopie de la GDT a son adresse */
    kl::memcpy((char *)gdt_ptr->base, (char *)gdt, gdt_ptr->limite);

	/* Chargement du registre GDTR */
    asm(
        "lgdtl (gdt_reg)\n\t"
       );

	/* Initialisation des segments */
    asm(
        "movw $0x10, %ax \n\t"
        "movw %ax, %ds \n\t"
        "movw %ax, %es \n\t"
        "movw %ax, %fs \n\t"
        "movw %ax, %gs \n\t"
        "ljmp $0x08, $next \n\t"
        "next:\n\t"
       );
}

}

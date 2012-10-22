#pragma once
#ifndef IDT_6RKZEFXQ
#define IDT_6RKZEFXQ

#include "types.h"

namespace interupt {

namespace {

void *idt_base = (void *)0x800;
unsigned int idt_size = 0xFF;
unsigned int int_gate = 0x8E00;

#pragma pack(push, 1)

/* Segment descriptor */
struct idt_desc {
	u16 offset0_15;
	u16 select;
	u16 type;
	u16 offset16_31;
};

/* IDTR register */
struct idt_reg {
	u16 limite;
	u32 base;
};
#pragma pack(pop)
}

}


#endif /* end of include guard: IDT_6RKZEFXQ */

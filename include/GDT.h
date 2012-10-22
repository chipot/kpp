#pragma once
#ifndef GDT_PL5MR4WN
#define GDT_PL5MR4WN

#include "types.h"

namespace memory {

namespace {

#pragma pack(push, 1)

/* Cette structure est completement débile*/
struct gdt_entry
{
    u16 lim0_15;    
    u16 base0_15;
    u8 base16_23;
    u8 acces;
    u8 lim16_19 : 4;
    u8 other : 4;
    u8 base24_31;
};

/* Registre GDTR */
struct gdtr
{
    u16 limite;
    u32 base;
};
#pragma pack(pop)

}

class GDT
{
  const unsigned int GDTSIZE = 0xFF;
  const unsigned int GDTBASE = 0x0;

 private:
  gdtr *gdt_ptr;
  gdt_entry gdt[0xFF];
  unsigned int _last_offset = 0;
 public:
  GDT();
  void add_entry(u32 base, u32 offset, u8 acces, u8 other);
  void commit();

};

}

extern "C" memory::gdtr gdt_reg; 

#endif /* end of include guard: GDT_PL5MR4WN */

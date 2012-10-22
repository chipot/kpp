global _start, start
extern kmain
extern __START__INIT__
extern __END__INIT__

%define MULTIBOOT_HEADER_MAGIC  0x1BADB002
%define MULTIBOOT_HEADER_FLAGS	0x00000003
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

_start:
	jmp start
; ----- The Multiboot header -----------
align 4
multiboot_header:
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd CHECKSUM     
; ----- Multiboot Header Ends Here -----

start:
	mov  ebx, __START__INIT__
	jmp  .ctors_until_end
	.call_constructor:
	call [ebx]
	add  ebx, 4
	.ctors_until_end:
	cmp  ebx, __END__INIT__
	jb   .call_constructor

	push ebx
	call kmain

	cli ; stop interrupts
	hlt ; halt the CPU


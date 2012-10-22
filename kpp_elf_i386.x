/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
	. = 0x100000;
	.text : {
		_TEXT_START_ = .;
		*(.text*)
		/**(.gnu.linkonce.t*)*/
		_TEXT_END_ = .;
	}

	.rodata : {

		/*start_ctors = .;
		*(SORT(.ctors*))
		end_ctors = .;

		start_dtors = .;
		*(SORT(.dtors*))
		end_dtors = .;*/

		_DATA_START_ = .;
		*(.rodata*)
		/**(.gnu.linkonce.r*)*/
		_DATA_END_ = .;
	}

	.data : {
		_DATA_START_ = .;
		*(.data*)
		/**(.gnu.linkonce.d*)*/
		_DATA_END_ = .;
	}

	.bss : {
		_BSS_START_ = .;
		*(.bss*)
		/**(.gnu.linkonce.b*)*/
		_BSS_END_ = .;
	}
	/DISCARD/ : {
		*(.note*)
	}
}

OUTPUT_ARCH( "riscv" )
ENTRY( _start )

MEMORY
{
	ram (wxa) : ORIGIN = 0x00000000, LENGTH = 128K
}

SECTIONS
{
	.init : { *(.init) } >ram
	.text : { *(.text) } >ram
	.data : { *(.data) } >ram
	.sdata : { *(.sdata) } >ram
	.bss : { *(.bss) } >ram
	.sbss : { *(.sbss) } >ram
	.stack :
	{
		. = ALIGN(16);
		. += 1000;
		_stack_top = .;
	} >ram
}

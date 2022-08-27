/* linker script CortexM3
Eng.Assem
*/

MEMORY
{
 flash (RX)  : ORIGIN = 0x08000000, LENGTH = 128k
 sram  (RWX) : ORIGIN = 0X20000000, LENGTH = 20K
}

SECTIONS
{
	.text :{
		*(.vectors*)
	        *(.text*)
		*(.rodata)
		. = ALIGN(4);
		_E_text = .;
	}>flash	
	
	.data :{
	        _S_DATA = .;
		*(.data)
		. = ALIGN(4);
	         _E_DATA = .;
	}>sram AT>flash

	.bss :{
	        _S_bss = .;
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		 _E_bss = .;
	}>sram	
	
	. = . + 0X1000;
	_stack_top = . ;
}

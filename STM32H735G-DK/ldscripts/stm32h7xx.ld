
SECTIONS {

	.sysmem : {
		_sys = . ;
		*(.sysmem)
		. = ALIGN(1024);
	} > sysmem
	_esys = .;

	. = 0;
	.backup : {
		_backup = . ;
		*(.backup)
	} >backup
	_ebackup = .;

	. = 0;
	INCLUDE stm32-common.ld
}

PROVIDE ( _end = . );
PROVIDE ( _top_of_stack = (ORIGIN(sysmem) + LENGTH(sysmem)) );
PROVIDE ( _estack = (ORIGIN(sysmem) + LENGTH(sysmem)) );
PROVIDE ( _flash_start = ORIGIN(flash) );
PROVIDE ( _flash_pages = flash_page_count );
PROVIDE ( _flash_size = LENGTH(flash) );
PROVIDE ( _ram_pages = ( (LENGTH(ram) + LENGTH(ram1) + LENGTH(ram2)) / 1024 ) );
PROVIDE ( _sram_size = LENGTH(ram) );
PROVIDE ( _sram_start = ORIGIN(ram) );
PROVIDE ( _sram1_size = LENGTH(ram1) );
PROVIDE ( _sram1_start = ORIGIN(ram1) );
PROVIDE ( _sram2_size = LENGTH(ram2) );
PROVIDE ( _sram2_start = ORIGIN(ram2) );
PROVIDE ( _unique_id = 0x1FF0F420 );

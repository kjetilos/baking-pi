/* link-arm-eabi.ld - linker script for arm eabi */
 
SECTIONS
{
  .init 0x8000 : {
    *(.init)
  }

  .text : {
    *(.text)
  }

  . = ALIGN(4096); /* align to page size */
  .rodata : {
    *(.rodata)
  }

  . = ALIGN(4096); /* align to page size */
  .data : {
    *(.data)
  }

  . = ALIGN(4096); /* align to page size */
  _bss_start = .;
  .bss : {
    bss = .;
    *(.bss)
  }
  .= ALIGN(4096);
  _bss_end = .;

  .comment : {
    *(.comment)
  }
}

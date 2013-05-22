/* link-arm-eabi.ld - linker script for arm eabi */
 
SECTIONS
{
  .init 0x0000 : {
    *(.init)
  }

  .text 0x8000 : {
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
  .bss : {
    bss = .;
    *(.bss)
  }

  .= ALIGN(4096);
  .comment : {
    *(.comment)
  }
}

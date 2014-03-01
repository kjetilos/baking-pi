.section .init
.globl _start
_start:
	mov sp, #0x8000

  mrc p15, 0, r0, c1, c0, 2
  orr r0, r0, #0x300000            @ single precision
  orr r0, r0, #0xC00000            @ double precision
  mcr p15, 0, r0, c1, c0, 2
  mov r0, #0x40000000
  fmxr fpexc,r0

	b main

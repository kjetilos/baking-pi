.section .init
.globl _start
_start:
	b main

.section .text
main:
	mov sp, #0x8000

	mov r0, #16
	mov r1, #1
	bl SetGpioFunction

	ldr r4, =pattern /* load address */
	ldr r4, [r4]     /* load content */
	mov r5, #0       /* sequence number */

loop:	
	/* r1 current pattern value */
	mov r1, #1
	lsl r1, r5
	and r1, r4

	mov r0, #16
	bl SetGpio
	ldr r0, =50000
	bl wait

	/* next index and wrap at 32 */
	add r5, #1
	cmp r5, #32
	moveq r5, #0
	
	b loop

.section .data
.align 2
pattern:
	.int 0b11111111101010100010001000101010

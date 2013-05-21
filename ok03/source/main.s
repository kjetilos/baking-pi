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

loop:	
	mov r0, #16
	mov r1, #0
	bl SetGpio
	bl wait

	mov r0, #16
	mov r1, #1
	bl SetGpio
	bl wait

	b loop

wait:
	mov r2, #0x3f0000
wait$:	sub r2, #1
	cmp r2, #0
	bne wait$
	mov pc, lr

.section .init
.globl _start
_start:
	ldr r0, =0x20200000	/* Address of GPIO Controller */

	/* Enable output on the 16th GPIO pin */
	mov r1, #1
	lsl r1, #18		/* Logical shift left */
	str r1, [r0,#4]

loop$:	
	/* Turn LED on */
	mov r1, #1
	lsl r1, #16
	str r1, [r0,#40]

	/* wait */
	mov r2, #0x3f0000
wait1$:
	sub r2, #1
	cmp r2, #0
	bne wait1$
	
	/* Turn LED off */
	mov r1, #1
	lsl r1, #16
	str r1, [r0,#28]

	/* wait again */
	mov r2, #0x3f0000
wait2$:
	sub r2, #1
	cmp r2, #0
	bne wait2$
	
	/* Loop back */
	b loop$

	

.section .init
.globl _start
_start:
	ldr r0, =0x20200000	/* Address of GPIO Controller */

	/* Enable output on the 16th GPIO pin */
	mov r1, #1
	lsl r1, #18		/* Logical shift left */
	str r1, [r0,#4]

	/* Turn LED on */
	mov r1, #1
	lsl r1, #16
	str r1, [r0,#40]

	/* Loop forever */
loop$:
	b loop$

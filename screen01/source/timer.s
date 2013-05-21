.globl wait
/*
  wait function
------------------
  r0 - time to wait
*/
wait:
	ldr r2, =0x20003000 /* Timer base address */
	ldr r1, [r2,#4] /* read value */
	add r0, r0, r1      /* add wait time */
read$:	ldr r1, [r2,#4]
	cmp r0, r1          /* a-b = r0 - r1 */
	bgt read$           /* branch if r0 - r1 > 0 */
	mov pc, lr

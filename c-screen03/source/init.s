.section .init
.globl _start
_start:
	mov sp, #0x8000

	/* Clear out bss. */
	ldr	r4, =_bss_start
	ldr	r9, =_bss_end
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r8, #0
        b       .L2
 
.L1:
	/* store multiple at r4. */
	stmia	r4!, {r5-r8}
 
	/* If we are still below bss_end, loop. */
.L2:
	cmp	r4, r9
	blo	.L1
	
	b main

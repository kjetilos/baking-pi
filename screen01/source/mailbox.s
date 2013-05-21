.globl GetMailboxBase
GetMailboxBase:
	ldr r0, =0x2000B880
	mov pc, lr

.globl MailboxWrite
MailboxWrite:
	tst r0, #0b1111
	movne pc, lr
	cmp r1, #15
	movhi pc, lr

	mov r2, r0
	push {lr}
	bl GetMailboxBase
wait1$:
	ldr r3, [r0, #0x18]
	tst status, #0x80000000
	bne wait1$

	add r2, r1
	str r2, [r0, #0x20]
	pop {pc}

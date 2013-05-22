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

	/* r2 = value */
	mov r2, r0
	push {lr}
	bl GetMailboxBase
wait1$:
	/* r3 = status */
	ldr r3, [r0, #0x18]
	tst r3, #0x80000000
	bne wait1$

	/* r1 = channel */
	add r2, r1
	str r2, [r0, #0x20]
	pop {pc}

.globl MailboxRead
MailboxRead:
	cmp r0, #15
	movhi pc, lr
	mov r1, r0
	push {lr}

	bl GetMailboxBase
	/* r0 = mailbox */
	/* r1 = channel */
rightmail$:
wait2$:
	ldr r2, [r0,#0x18]
	tst r2, #0x40000000
	bne wait2$

	/* r1 = channel */
	/* r2 = mail */
	/* r3 = input channel */
	ldr r2, [r0,#0]
	and r3, r2, #0b1111
	teq r3, r1
	bne rightmail$

	/* returns the top 28 bits of the mail */
	and r0, r2, #0xfffffff0
	pop {pc}



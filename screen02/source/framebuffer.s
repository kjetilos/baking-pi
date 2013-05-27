.section .data
.align 12
.globl FrameBufferInfo
FrameBufferInfo:
	.int 1024 /* #0 Width */
	.int 768  /* #4 Height */
	.int 1024 /* #8 vWidth */
	.int 768  /* #12 vHeight */
	.int 0    /* #16 GPU - Pitch */
	.int 16   /* #20 Bit Depth */
	.int 0    /* #24 X */
	.int 0    /* #28 Y */
	.int 0    /* #32 GPU - Pointer */
	.int 0    /* #36 GPU - Size */

.section .text
.globl InitializeFrameBuffer
InitializeFrameBuffer:
	/* r0 = width */
	/* r1 = height */
	/* r2 = depth */
	cmp r0, #4096
	cmpls r1, #4096
	cmpls r2, #32
	movhi r0, #0
	movhi pc, lr

	push {r4, lr}
	ldr r4, =FrameBufferInfo
	str r0, [r4,#0]
	str r1, [r4,#4]
	str r0, [r4,#8]
	str r1, [r4,#12]
	str r2, [r4,#20]

	/* Send request to GPU */
	mov r0, r4
	mov r1, #1
	bl MailboxWrite

	/* Read response from GPU */
	mov r0, #1
	bl MailboxRead

	teq r0, #0
	movne r0, #0
	popne {r4, pc}

pointerWait$:
	ldr r0, [r4, #32]
	teq r0, #0
	beq pointerWait$

	mov r0, r4
	pop {r4, pc}
	

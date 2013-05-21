	.cpu arm10tdmi
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	ldr	r3, .L7
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	add	r3, r3, #4
	mov	r2, #262144
	str	r2, [r3, #0]
.L6:
	ldr	r3, [fp, #-12]
	add	r3, r3, #40
	mov	r2, #65536
	str	r2, [r3, #0]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L3:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r2, [fp, #-8]
	ldr	r3, .L7+4
	cmp	r2, r3
	ble	.L3
	ldr	r3, [fp, #-12]
	add	r3, r3, #28
	mov	r2, #65536
	str	r2, [r3, #0]
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L4
.L5:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L4:
	ldr	r2, [fp, #-8]
	ldr	r3, .L7+4
	cmp	r2, r3
	ble	.L5
	b	.L6
.L8:
	.align	2
.L7:
	.word	538968064
	.word	4128767
	.size	main, .-main
	.ident	"GCC: (crosstool-NG hg+unknown-20130108.083332) 4.7.2 20120910 (prerelease)"
	.section	.note.GNU-stack,"",%progbits

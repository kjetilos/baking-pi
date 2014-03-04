.section .init
.globl _start
_start:
  ldr pc,reset_handler
  ldr pc,undefined_handler
  ldr pc,swi_handler
  ldr pc,prefetch_handler
  ldr pc,data_handler
  ldr pc,unused_handler
  ldr pc,irq_handler
  ldr pc,fiq_handler
reset_handler:      .word reset
undefined_handler:  .word hang
swi_handler:        .word hang
prefetch_handler:   .word hang
data_handler:       .word hang
unused_handler:     .word hang
irq_handler:        .word irq
fiq_handler:        .word hang

reset:
  /* Copy the Vector Table over to address 0x0000 0000 
     which is the default interrupt vector address */
  mov r0, #0x8000
  mov r1, #0x0000
  ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
  stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
  ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
  stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

  /* Switch to IRQ Mode and setup stack pointer */
  cps #0x12    @ IRQ Mode
  mov sp, #0x3000
  /* Switch to Supervisor Mode and setup stack pointer */
  cps #0x13    @ supervisor mode
  mov sp, #0x8000

	b main

hang: 
  b hang

irq:
  push {r0,r1,r2,r3,r4,r5,r6,r7,lr}
  bl c_irq_handler
  pop  {r0,r1,r2,r3,r4,r5,r6,r7,lr}
  subs pc,lr,#4

.globl enable_irq
enable_irq:
  cpsie i
  bx lr

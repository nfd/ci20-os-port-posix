#include "mipsregs.h"

.section .text.start
.set noreorder

/* make it accessible outside */
.globl _start
/* Tell binutils it's a function */
.ent _start
.text

_start:
	/* Clear BSS */
	la      t0, __bss_start
	la      t1, __bss_end - 4
1:
	sw      zero, 0(t0)
	blt     t0, t1, 1b
	addiu   t0, t0, 4

	/* Set up a stack at 256M-8M */
	li sp, 0x8f800000

	/* Do baremetal init */
	la t0, libci20_init_baremetal
	jal t0
	nop

	/* And jump to C */
	la t0, main
	jr t0
	nop

.end _start


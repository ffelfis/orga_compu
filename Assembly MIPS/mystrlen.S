#include <sys/regdef.h>

	.text
	.align	2
	.globl	mystrlen
	.ent	mystrlen

mystrlen:
	.frame	fp, 16, ra
	.set	noreorder
	.cpload	t9
	.set	reorder

	subu	sp, sp, 16
	.cprestore 0
	sw	fp, 4(sp)
	move	fp, sp
	li	v0, 0

mystrlen_loop:
	lb	t0, 0(a0)
	beqz	t0, mystrlen_return
	addiu	a0, a0, 1
	addiu	v0, v0, 1
	j	mystrlen_loop

mystrlen_return:
	lw	fp, 4(sp)
	addu	sp, sp, 16
	j	ra
	.end	mystrlen

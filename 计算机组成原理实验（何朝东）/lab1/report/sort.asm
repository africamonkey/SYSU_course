.text
.globl main
main:
	li	$t0,	10
	la	$t1,	data
read:
	li	$v0,	5
	syscall
	sw	$v0,	0($t1)
	addi	$t1,	$t1,	4
	addi	$t0,	$t0,	-1
	bne	$t0,	$zero,	read

	li	$t0,	10
l1:
	addi	$t0,	$t0,	-1
	la	$t1,	data
	li	$t2,	9
l2:
	addi	$t3,	$t1,	4
	addi	$t2,	$t2,	-1
	lw	$t4,	0($t1)
	lw	$t5,	0($t3)
	slt	$t6,	$t4,	$t5
	beq	$t6,	$zero,	dnswap
	move	$t6,	$t4
	move	$t4,	$t5
	move	$t5,	$t6
dnswap:
	sw	$t4,	0($t1)
	sw	$t5,	0($t3)
	move	$t1,	$t3
	bne	$t2,	$zero,	l2
	bne	$t0,	$zero,	l1

	li	$t0,	10
	la	$t1,	data
write:
	lw	$a0,	0($t1)
	li	$v0,	1
	syscall
	li	$a0,	32
	li	$v0,	11
	syscall
	addi	$t1,	$t1,	4
	addi	$t0,	$t0,	-1
	bne	$t0,	$zero,	write

	li	$a0,	0x0a
	li	$v0,	11
	syscall
	li	$a0,	0x0d
	li	$v0,	11
	syscall
	li	$v0,	10
	syscall
.data
	data: .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000

add-consts:     file format elf32-tradlittlemips

Disassembly of section .text:

004000b0 <__start>:
  4000b0:	3c1c1000 	lui	gp,0x1000
  4000b4:	279c7ff0 	addiu	gp,gp,32752
  4000b8:	0000f821 	move	ra,zero
  4000bc:	8fa40000 	lw	a0,0(sp)
  4000c0:	27a50004 	addiu	a1,sp,4
  4000c4:	2401fff8 	li	at,-8
  4000c8:	03a1e824 	and	sp,sp,at
  4000cc:	27bdffe8 	addiu	sp,sp,-24
  4000d0:	afbf0014 	sw	ra,20(sp)
  4000d4:	24860001 	addiu	a2,a0,1
  4000d8:	00063080 	sll	a2,a2,0x2
  4000dc:	3c190040 	lui	t9,0x40
  4000e0:	27390110 	addiu	t9,t9,272
  4000e4:	00c53020 	add	a2,a2,a1
  4000e8:	3c011000 	lui	at,0x1000
  4000ec:	0320f809 	jalr	t9
  4000f0:	ac260000 	sw	a2,0(at)
  4000f4:	3c190040 	lui	t9,0x40
  4000f8:	27390120 	addiu	t9,t9,288
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	03e00008 	jr	ra
  400114:	24020007 	li	v0,7
	...

00400120 <_exit>:
  400120:	24020fa1 	li	v0,4001
  400124:	0000000c 	syscall

00400128 <__unified_syscall>:
  400128:	14e00003 	bnez	a3,400138 <error_unified_syscall>
  40012c:	00000000 	nop

00400130 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  400130:	03e00008 	jr	ra
  400134:	00000000 	nop

00400138 <error_unified_syscall>:
  400138:	27bdffe8 	addiu	sp,sp,-24
  40013c:	afbf0000 	sw	ra,0(sp)
  400140:	afa20004 	sw	v0,4(sp)
  400144:	3c190040 	lui	t9,0x40
  400148:	27390170 	addiu	t9,t9,368
  40014c:	0320f809 	jalr	t9
  400150:	00000000 	nop
  400154:	8fa80004 	lw	t0,4(sp)
  400158:	8fbf0000 	lw	ra,0(sp)
  40015c:	ac480000 	sw	t0,0(v0)
  400160:	2402ffff 	li	v0,-1
  400164:	03e00008 	jr	ra
  400168:	27bd0018 	addiu	sp,sp,24
  40016c:	00000000 	nop

00400170 <__errno_location>:
  400170:	3c021000 	lui	v0,0x1000
  400174:	03e00008 	jr	ra
  400178:	24420100 	addiu	v0,v0,256
  40017c:	00000000 	nop

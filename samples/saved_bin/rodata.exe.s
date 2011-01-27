
rodata:     file format elf32-tradlittlemips

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
  4000f8:	273901c0 	addiu	t9,t9,448
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	3c020040 	lui	v0,0x40
  400114:	27bdffa8 	addiu	sp,sp,-88
  400118:	24460240 	addiu	a2,v0,576
  40011c:	afbf0050 	sw	ra,80(sp)
  400120:	27a90010 	addiu	t1,sp,16
  400124:	24c70030 	addiu	a3,a2,48
  400128:	8cc20000 	lw	v0,0(a2)
  40012c:	8cc30004 	lw	v1,4(a2)
  400130:	8cc40008 	lw	a0,8(a2)
  400134:	8cc5000c 	lw	a1,12(a2)
  400138:	24c60010 	addiu	a2,a2,16
  40013c:	ad220000 	sw	v0,0(t1)
  400140:	ad230004 	sw	v1,4(t1)
  400144:	ad240008 	sw	a0,8(t1)
  400148:	ad25000c 	sw	a1,12(t1)
  40014c:	14c7fff6 	bne	a2,a3,400128 <main+0x18>
  400150:	25290010 	addiu	t1,t1,16
  400154:	8cc30000 	lw	v1,0(a2)
  400158:	8cc70004 	lw	a3,4(a2)
  40015c:	8cc80008 	lw	t0,8(a2)
  400160:	94c2000c 	lhu	v0,12(a2)
  400164:	27a50010 	addiu	a1,sp,16
  400168:	24040001 	li	a0,1
  40016c:	2406003e 	li	a2,62
  400170:	a522000c 	sh	v0,12(t1)
  400174:	ad230000 	sw	v1,0(t1)
  400178:	ad270004 	sw	a3,4(t1)
  40017c:	0c100084 	jal	400210 <__libc_write>
  400180:	ad280008 	sw	t0,8(t1)
  400184:	27a5001f 	addiu	a1,sp,31
  400188:	24040001 	li	a0,1
  40018c:	0c100084 	jal	400210 <__libc_write>
  400190:	24060001 	li	a2,1
  400194:	3c050040 	lui	a1,0x40
  400198:	24a50280 	addiu	a1,a1,640
  40019c:	24040001 	li	a0,1
  4001a0:	0c100084 	jal	400210 <__libc_write>
  4001a4:	24060001 	li	a2,1
  4001a8:	8fbf0050 	lw	ra,80(sp)
  4001ac:	00001021 	move	v0,zero
  4001b0:	03e00008 	jr	ra
  4001b4:	27bd0058 	addiu	sp,sp,88
	...

004001c0 <_exit>:
  4001c0:	24020fa1 	li	v0,4001
  4001c4:	0000000c 	syscall

004001c8 <__unified_syscall>:
  4001c8:	14e00003 	bnez	a3,4001d8 <error_unified_syscall>
  4001cc:	00000000 	nop

004001d0 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  4001d0:	03e00008 	jr	ra
  4001d4:	00000000 	nop

004001d8 <error_unified_syscall>:
  4001d8:	27bdffe8 	addiu	sp,sp,-24
  4001dc:	afbf0000 	sw	ra,0(sp)
  4001e0:	afa20004 	sw	v0,4(sp)
  4001e4:	3c190040 	lui	t9,0x40
  4001e8:	27390230 	addiu	t9,t9,560
  4001ec:	0320f809 	jalr	t9
  4001f0:	00000000 	nop
  4001f4:	8fa80004 	lw	t0,4(sp)
  4001f8:	8fbf0000 	lw	ra,0(sp)
  4001fc:	ac480000 	sw	t0,0(v0)
  400200:	2402ffff 	li	v0,-1
  400204:	03e00008 	jr	ra
  400208:	27bd0018 	addiu	sp,sp,24
  40020c:	00000000 	nop

00400210 <__libc_write>:
  400210:	24020fa4 	li	v0,4004
  400214:	0000000c 	syscall
  400218:	3c190040 	lui	t9,0x40
  40021c:	273901c8 	addiu	t9,t9,456
  400220:	03200008 	jr	t9
  400224:	00000000 	nop
	...

00400230 <__errno_location>:
  400230:	3c021000 	lui	v0,0x1000
  400234:	03e00008 	jr	ra
  400238:	24420100 	addiu	v0,v0,256
  40023c:	00000000 	nop


strlen:     file format elf32-tradlittlemips

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
  4000f8:	27390200 	addiu	t9,t9,512
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	27bdffb8 	addiu	sp,sp,-72
  400114:	3c030040 	lui	v1,0x40
  400118:	afb5003c 	sw	s5,60(sp)
  40011c:	afb40038 	sw	s4,56(sp)
  400120:	afb30034 	sw	s3,52(sp)
  400124:	afb20030 	sw	s2,48(sp)
  400128:	afbf0040 	sw	ra,64(sp)
  40012c:	afb1002c 	sw	s1,44(sp)
  400130:	afb00028 	sw	s0,40(sp)
  400134:	24620380 	addiu	v0,v1,896
  400138:	8c640380 	lw	a0,896(v1)
  40013c:	8c480014 	lw	t0,20(v0)
  400140:	8c450004 	lw	a1,4(v0)
  400144:	8c430008 	lw	v1,8(v0)
  400148:	8c46000c 	lw	a2,12(v0)
  40014c:	8c470010 	lw	a3,16(v0)
  400150:	afa40010 	sw	a0,16(sp)
  400154:	afa50014 	sw	a1,20(sp)
  400158:	afa30018 	sw	v1,24(sp)
  40015c:	afa6001c 	sw	a2,28(sp)
  400160:	afa70020 	sw	a3,32(sp)
  400164:	afa80024 	sw	t0,36(sp)
  400168:	3c150040 	lui	s5,0x40
  40016c:	24140001 	li	s4,1
  400170:	27b30010 	addiu	s3,sp,16
  400174:	24120005 	li	s2,5
  400178:	8e700000 	lw	s0,0(s3)
  40017c:	2652ffff 	addiu	s2,s2,-1
  400180:	0c1000a0 	jal	400280 <strlen>
  400184:	02002021 	move	a0,s0
  400188:	00403021 	move	a2,v0
  40018c:	02002821 	move	a1,s0
  400190:	24040001 	li	a0,1
  400194:	0c100094 	jal	400250 <__libc_write>
  400198:	00408821 	move	s1,v0
  40019c:	26730004 	addiu	s3,s3,4
  4001a0:	24040001 	li	a0,1
  4001a4:	26a5037c 	addiu	a1,s5,892
  4001a8:	14510010 	bne	v0,s1,4001ec <main+0xdc>
  4001ac:	24060001 	li	a2,1
  4001b0:	0c100094 	jal	400250 <__libc_write>
  4001b4:	00000000 	nop
  4001b8:	1454000c 	bne	v0,s4,4001ec <main+0xdc>
  4001bc:	00000000 	nop
  4001c0:	0641ffed 	bgez	s2,400178 <main+0x68>
  4001c4:	00001021 	move	v0,zero
  4001c8:	8fbf0040 	lw	ra,64(sp)
  4001cc:	8fb5003c 	lw	s5,60(sp)
  4001d0:	8fb40038 	lw	s4,56(sp)
  4001d4:	8fb30034 	lw	s3,52(sp)
  4001d8:	8fb20030 	lw	s2,48(sp)
  4001dc:	8fb1002c 	lw	s1,44(sp)
  4001e0:	8fb00028 	lw	s0,40(sp)
  4001e4:	03e00008 	jr	ra
  4001e8:	27bd0048 	addiu	sp,sp,72
  4001ec:	0c100080 	jal	400200 <_exit>
  4001f0:	24040002 	li	a0,2
	...

00400200 <_exit>:
  400200:	24020fa1 	li	v0,4001
  400204:	0000000c 	syscall

00400208 <__unified_syscall>:
  400208:	14e00003 	bnez	a3,400218 <error_unified_syscall>
  40020c:	00000000 	nop

00400210 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  400210:	03e00008 	jr	ra
  400214:	00000000 	nop

00400218 <error_unified_syscall>:
  400218:	27bdffe8 	addiu	sp,sp,-24
  40021c:	afbf0000 	sw	ra,0(sp)
  400220:	afa20004 	sw	v0,4(sp)
  400224:	3c190040 	lui	t9,0x40
  400228:	27390270 	addiu	t9,t9,624
  40022c:	0320f809 	jalr	t9
  400230:	00000000 	nop
  400234:	8fa80004 	lw	t0,4(sp)
  400238:	8fbf0000 	lw	ra,0(sp)
  40023c:	ac480000 	sw	t0,0(v0)
  400240:	2402ffff 	li	v0,-1
  400244:	03e00008 	jr	ra
  400248:	27bd0018 	addiu	sp,sp,24
  40024c:	00000000 	nop

00400250 <__libc_write>:
  400250:	24020fa4 	li	v0,4004
  400254:	0000000c 	syscall
  400258:	3c190040 	lui	t9,0x40
  40025c:	27390208 	addiu	t9,t9,520
  400260:	03200008 	jr	t9
  400264:	00000000 	nop
	...

00400270 <__errno_location>:
  400270:	3c021000 	lui	v0,0x1000
  400274:	03e00008 	jr	ra
  400278:	24420100 	addiu	v0,v0,256
  40027c:	00000000 	nop

00400280 <strlen>:
  400280:	27bdfff8 	addiu	sp,sp,-8
  400284:	00803021 	move	a2,a0
  400288:	10800025 	beqz	a0,400320 <strlen+0xa0>
  40028c:	00001021 	move	v0,zero
  400290:	081000a8 	j	4002a0 <strlen+0x20>
  400294:	30820003 	andi	v0,a0,0x3
  400298:	081000c8 	j	400320 <strlen+0xa0>
  40029c:	00c41023 	subu	v0,a2,a0
  4002a0:	10400008 	beqz	v0,4002c4 <strlen+0x44>
  4002a4:	00000000 	nop
  4002a8:	80c20000 	lb	v0,0(a2)
  4002ac:	00000000 	nop
  4002b0:	1040fff9 	beqz	v0,400298 <strlen+0x18>
  4002b4:	00000000 	nop
  4002b8:	24c60001 	addiu	a2,a2,1
  4002bc:	081000a8 	j	4002a0 <strlen+0x20>
  4002c0:	30c20003 	andi	v0,a2,0x3
  4002c4:	8cc50000 	lw	a1,0(a2)
  4002c8:	3c02fefe 	lui	v0,0xfefe
  4002cc:	3442feff 	ori	v0,v0,0xfeff
  4002d0:	00a21021 	addu	v0,a1,v0
  4002d4:	00051827 	nor	v1,zero,a1
  4002d8:	00432824 	and	a1,v0,v1
  4002dc:	3c028080 	lui	v0,0x8080
  4002e0:	34428080 	ori	v0,v0,0x8080
  4002e4:	00a22824 	and	a1,a1,v0
  4002e8:	10a0fff6 	beqz	a1,4002c4 <strlen+0x44>
  4002ec:	24c60004 	addiu	a2,a2,4
  4002f0:	3c020404 	lui	v0,0x404
  4002f4:	24a3ffff 	addiu	v1,a1,-1
  4002f8:	34420400 	ori	v0,v0,0x400
  4002fc:	00622824 	and	a1,v1,v0
  400300:	00051200 	sll	v0,a1,0x8
  400304:	00051c00 	sll	v1,a1,0x10
  400308:	00431021 	addu	v0,v0,v1
  40030c:	00a22821 	addu	a1,a1,v0
  400310:	00051682 	srl	v0,a1,0x1a
  400314:	00c23021 	addu	a2,a2,v0
  400318:	00c41023 	subu	v0,a2,a0
  40031c:	2442fffc 	addiu	v0,v0,-4
  400320:	03e00008 	jr	ra
  400324:	27bd0008 	addiu	sp,sp,8
	...

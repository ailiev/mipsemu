
strcmp:     file format elf32-tradlittlemips

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
  4000f8:	273902a0 	addiu	t9,t9,672
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	27bdfb18 	addiu	sp,sp,-1256
  400114:	3c020040 	lui	v0,0x40
  400118:	24460500 	addiu	a2,v0,1280
  40011c:	27a90010 	addiu	t1,sp,16
  400120:	afbf04e4 	sw	ra,1252(sp)
  400124:	afb604e0 	sw	s6,1248(sp)
  400128:	afb504dc 	sw	s5,1244(sp)
  40012c:	afb404d8 	sw	s4,1240(sp)
  400130:	afb304d4 	sw	s3,1236(sp)
  400134:	afb204d0 	sw	s2,1232(sp)
  400138:	afb104cc 	sw	s1,1228(sp)
  40013c:	afb004c8 	sw	s0,1224(sp)
  400140:	01203821 	move	a3,t1
  400144:	24c804a0 	addiu	t0,a2,1184
  400148:	8cc20000 	lw	v0,0(a2)
  40014c:	8cc30004 	lw	v1,4(a2)
  400150:	8cc40008 	lw	a0,8(a2)
  400154:	8cc5000c 	lw	a1,12(a2)
  400158:	24c60010 	addiu	a2,a2,16
  40015c:	ace20000 	sw	v0,0(a3)
  400160:	ace30004 	sw	v1,4(a3)
  400164:	ace40008 	sw	a0,8(a3)
  400168:	ace5000c 	sw	a1,12(a3)
  40016c:	14c8fff6 	bne	a2,t0,400148 <main+0x38>
  400170:	24e70010 	addiu	a3,a3,16
  400174:	3c030040 	lui	v1,0x40
  400178:	3c040040 	lui	a0,0x40
  40017c:	8cc20000 	lw	v0,0(a2)
  400180:	8c9409b8 	lw	s4,2488(a0)
  400184:	8c7509b0 	lw	s5,2480(v1)
  400188:	ace20000 	sw	v0,0(a3)
  40018c:	247309b0 	addiu	s3,v1,2480
  400190:	01208021 	move	s0,t1
  400194:	00008821 	move	s1,zero
  400198:	249609b8 	addiu	s6,a0,2488
  40019c:	26120040 	addiu	s2,s0,64
  4001a0:	02002021 	move	a0,s0
  4001a4:	0c1000c8 	jal	400320 <strcmp>
  4001a8:	02402821 	move	a1,s2
  4001ac:	8e030080 	lw	v1,128(s0)
  4001b0:	26310001 	addiu	s1,s1,1
  4001b4:	2c420001 	sltiu	v0,v0,1
  4001b8:	1443000e 	bne	v0,v1,4001f4 <main+0xe4>
  4001bc:	2e240009 	sltiu	a0,s1,9
  4001c0:	1480fff6 	bnez	a0,40019c <main+0x8c>
  4001c4:	26100084 	addiu	s0,s0,132
  4001c8:	8fbf04e4 	lw	ra,1252(sp)
  4001cc:	8fb604e0 	lw	s6,1248(sp)
  4001d0:	8fb504dc 	lw	s5,1244(sp)
  4001d4:	8fb404d8 	lw	s4,1240(sp)
  4001d8:	8fb304d4 	lw	s3,1236(sp)
  4001dc:	8fb204d0 	lw	s2,1232(sp)
  4001e0:	8fb104cc 	lw	s1,1228(sp)
  4001e4:	8fb004c8 	lw	s0,1224(sp)
  4001e8:	00001021 	move	v0,zero
  4001ec:	03e00008 	jr	ra
  4001f0:	27bd04e8 	addiu	sp,sp,1256
  4001f4:	8e620004 	lw	v0,4(s3)
  4001f8:	27a504b8 	addiu	a1,sp,1208
  4001fc:	24060008 	li	a2,8
  400200:	24040001 	li	a0,1
  400204:	afb504b8 	sw	s5,1208(sp)
  400208:	0c1000bc 	jal	4002f0 <__libc_write>
  40020c:	afa204bc 	sw	v0,1212(sp)
  400210:	0c100114 	jal	400450 <strlen>
  400214:	02002021 	move	a0,s0
  400218:	00403021 	move	a2,v0
  40021c:	02002821 	move	a1,s0
  400220:	0c1000bc 	jal	4002f0 <__libc_write>
  400224:	24040001 	li	a0,1
  400228:	92c30004 	lbu	v1,4(s6)
  40022c:	27a504c0 	addiu	a1,sp,1216
  400230:	24060005 	li	a2,5
  400234:	24040001 	li	a0,1
  400238:	a3a304c4 	sb	v1,1220(sp)
  40023c:	0c1000bc 	jal	4002f0 <__libc_write>
  400240:	afb404c0 	sw	s4,1216(sp)
  400244:	0c100114 	jal	400450 <strlen>
  400248:	02402021 	move	a0,s2
  40024c:	00403021 	move	a2,v0
  400250:	02402821 	move	a1,s2
  400254:	0c1000bc 	jal	4002f0 <__libc_write>
  400258:	24040001 	li	a0,1
  40025c:	3c050040 	lui	a1,0x40
  400260:	24a509c0 	addiu	a1,a1,2496
  400264:	24040001 	li	a0,1
  400268:	0c1000bc 	jal	4002f0 <__libc_write>
  40026c:	24060001 	li	a2,1
  400270:	8fbf04e4 	lw	ra,1252(sp)
  400274:	8fb604e0 	lw	s6,1248(sp)
  400278:	8fb504dc 	lw	s5,1244(sp)
  40027c:	8fb404d8 	lw	s4,1240(sp)
  400280:	8fb304d4 	lw	s3,1236(sp)
  400284:	8fb204d0 	lw	s2,1232(sp)
  400288:	8fb104cc 	lw	s1,1228(sp)
  40028c:	8fb004c8 	lw	s0,1224(sp)
  400290:	24020002 	li	v0,2
  400294:	03e00008 	jr	ra
  400298:	27bd04e8 	addiu	sp,sp,1256
  40029c:	00000000 	nop

004002a0 <_exit>:
  4002a0:	24020fa1 	li	v0,4001
  4002a4:	0000000c 	syscall

004002a8 <__unified_syscall>:
  4002a8:	14e00003 	bnez	a3,4002b8 <error_unified_syscall>
  4002ac:	00000000 	nop

004002b0 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  4002b0:	03e00008 	jr	ra
  4002b4:	00000000 	nop

004002b8 <error_unified_syscall>:
  4002b8:	27bdffe8 	addiu	sp,sp,-24
  4002bc:	afbf0000 	sw	ra,0(sp)
  4002c0:	afa20004 	sw	v0,4(sp)
  4002c4:	3c190040 	lui	t9,0x40
  4002c8:	27390310 	addiu	t9,t9,784
  4002cc:	0320f809 	jalr	t9
  4002d0:	00000000 	nop
  4002d4:	8fa80004 	lw	t0,4(sp)
  4002d8:	8fbf0000 	lw	ra,0(sp)
  4002dc:	ac480000 	sw	t0,0(v0)
  4002e0:	2402ffff 	li	v0,-1
  4002e4:	03e00008 	jr	ra
  4002e8:	27bd0018 	addiu	sp,sp,24
  4002ec:	00000000 	nop

004002f0 <__libc_write>:
  4002f0:	24020fa4 	li	v0,4004
  4002f4:	0000000c 	syscall
  4002f8:	3c190040 	lui	t9,0x40
  4002fc:	273902a8 	addiu	t9,t9,680
  400300:	03200008 	jr	t9
  400304:	00000000 	nop
	...

00400310 <__errno_location>:
  400310:	3c021000 	lui	v0,0x1000
  400314:	03e00008 	jr	ra
  400318:	24420100 	addiu	v0,v0,256
  40031c:	00000000 	nop

00400320 <strcmp>:
  400320:	30830003 	andi	v1,a0,0x3
  400324:	30a20003 	andi	v0,a1,0x3
  400328:	10620010 	beq	v1,v0,40036c <strcmp+0x4c>
  40032c:	00000000 	nop
  400330:	80830000 	lb	v1,0(a0)
  400334:	081000d6 	j	400358 <strcmp+0x38>
  400338:	00000000 	nop
  40033c:	80a20000 	lb	v0,0(a1)
  400340:	00000000 	nop
  400344:	14620006 	bne	v1,v0,400360 <strcmp+0x40>
  400348:	00000000 	nop
  40034c:	24840001 	addiu	a0,a0,1
  400350:	80830000 	lb	v1,0(a0)
  400354:	24a50001 	addiu	a1,a1,1
  400358:	1460fff8 	bnez	v1,40033c <strcmp+0x1c>
  40035c:	00000000 	nop
  400360:	80830000 	lb	v1,0(a0)
  400364:	081000ed 	j	4003b4 <strcmp+0x94>
  400368:	00000000 	nop
  40036c:	10600017 	beqz	v1,4003cc <strcmp+0xac>
  400370:	3c02fefe 	lui	v0,0xfefe
  400374:	24020004 	li	v0,4
  400378:	00433023 	subu	a2,v0,v1
  40037c:	10c00013 	beqz	a2,4003cc <strcmp+0xac>
  400380:	3c02fefe 	lui	v0,0xfefe
  400384:	24c6ffff 	addiu	a2,a2,-1
  400388:	2402ffff 	li	v0,-1
  40038c:	10c2000e 	beq	a2,v0,4003c8 <strcmp+0xa8>
  400390:	2407ffff 	li	a3,-1
  400394:	80830000 	lb	v1,0(a0)
  400398:	24c6ffff 	addiu	a2,a2,-1
  40039c:	10600005 	beqz	v1,4003b4 <strcmp+0x94>
  4003a0:	24840001 	addiu	a0,a0,1
  4003a4:	80a20000 	lb	v0,0(a1)
  4003a8:	00000000 	nop
  4003ac:	10620004 	beq	v1,v0,4003c0 <strcmp+0xa0>
  4003b0:	00000000 	nop
  4003b4:	80a20000 	lb	v0,0(a1)
  4003b8:	03e00008 	jr	ra
  4003bc:	00621023 	subu	v0,v1,v0
  4003c0:	14c7fff4 	bne	a2,a3,400394 <strcmp+0x74>
  4003c4:	24a50001 	addiu	a1,a1,1
  4003c8:	3c02fefe 	lui	v0,0xfefe
  4003cc:	344afeff 	ori	t2,v0,0xfeff
  4003d0:	3c028080 	lui	v0,0x8080
  4003d4:	00804021 	move	t0,a0
  4003d8:	34498080 	ori	t1,v0,0x8080
  4003dc:	8d020000 	lw	v0,0(t0)
  4003e0:	8ca30000 	lw	v1,0(a1)
  4003e4:	004a2021 	addu	a0,v0,t2
  4003e8:	00403821 	move	a3,v0
  4003ec:	00021027 	nor	v0,zero,v0
  4003f0:	00822024 	and	a0,a0,v0
  4003f4:	00603021 	move	a2,v1
  4003f8:	006a1021 	addu	v0,v1,t2
  4003fc:	00031827 	nor	v1,zero,v1
  400400:	00431024 	and	v0,v0,v1
  400404:	00892024 	and	a0,a0,t1
  400408:	00491024 	and	v0,v0,t1
  40040c:	25080004 	addiu	t0,t0,4
  400410:	14800005 	bnez	a0,400428 <strcmp+0x108>
  400414:	24a50004 	addiu	a1,a1,4
  400418:	14400004 	bnez	v0,40042c <strcmp+0x10c>
  40041c:	30e200ff 	andi	v0,a3,0xff
  400420:	10e6ffee 	beq	a3,a2,4003dc <strcmp+0xbc>
  400424:	00000000 	nop
  400428:	30e200ff 	andi	v0,a3,0xff
  40042c:	30c300ff 	andi	v1,a2,0xff
  400430:	00073a02 	srl	a3,a3,0x8
  400434:	10400003 	beqz	v0,400444 <strcmp+0x124>
  400438:	00063202 	srl	a2,a2,0x8
  40043c:	1043fffa 	beq	v0,v1,400428 <strcmp+0x108>
  400440:	00000000 	nop
  400444:	03e00008 	jr	ra
  400448:	00431023 	subu	v0,v0,v1
  40044c:	00000000 	nop

00400450 <strlen>:
  400450:	27bdfff8 	addiu	sp,sp,-8
  400454:	00803021 	move	a2,a0
  400458:	10800025 	beqz	a0,4004f0 <strlen+0xa0>
  40045c:	00001021 	move	v0,zero
  400460:	0810011c 	j	400470 <strlen+0x20>
  400464:	30820003 	andi	v0,a0,0x3
  400468:	0810013c 	j	4004f0 <strlen+0xa0>
  40046c:	00c41023 	subu	v0,a2,a0
  400470:	10400008 	beqz	v0,400494 <strlen+0x44>
  400474:	00000000 	nop
  400478:	80c20000 	lb	v0,0(a2)
  40047c:	00000000 	nop
  400480:	1040fff9 	beqz	v0,400468 <strlen+0x18>
  400484:	00000000 	nop
  400488:	24c60001 	addiu	a2,a2,1
  40048c:	0810011c 	j	400470 <strlen+0x20>
  400490:	30c20003 	andi	v0,a2,0x3
  400494:	8cc50000 	lw	a1,0(a2)
  400498:	3c02fefe 	lui	v0,0xfefe
  40049c:	3442feff 	ori	v0,v0,0xfeff
  4004a0:	00a21021 	addu	v0,a1,v0
  4004a4:	00051827 	nor	v1,zero,a1
  4004a8:	00432824 	and	a1,v0,v1
  4004ac:	3c028080 	lui	v0,0x8080
  4004b0:	34428080 	ori	v0,v0,0x8080
  4004b4:	00a22824 	and	a1,a1,v0
  4004b8:	10a0fff6 	beqz	a1,400494 <strlen+0x44>
  4004bc:	24c60004 	addiu	a2,a2,4
  4004c0:	3c020404 	lui	v0,0x404
  4004c4:	24a3ffff 	addiu	v1,a1,-1
  4004c8:	34420400 	ori	v0,v0,0x400
  4004cc:	00622824 	and	a1,v1,v0
  4004d0:	00051200 	sll	v0,a1,0x8
  4004d4:	00051c00 	sll	v1,a1,0x10
  4004d8:	00431021 	addu	v0,v0,v1
  4004dc:	00a22821 	addu	a1,a1,v0
  4004e0:	00051682 	srl	v0,a1,0x1a
  4004e4:	00c23021 	addu	a2,a2,v0
  4004e8:	00c41023 	subu	v0,a2,a0
  4004ec:	2442fffc 	addiu	v0,v0,-4
  4004f0:	03e00008 	jr	ra
  4004f4:	27bd0008 	addiu	sp,sp,8
	...

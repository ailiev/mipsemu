
strcat:     file format elf32-tradlittlemips

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
  4000f8:	273901d0 	addiu	t9,t9,464
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	27bdff40 	addiu	sp,sp,-192
  400114:	3c030040 	lui	v1,0x40
  400118:	afb300b4 	sw	s3,180(sp)
  40011c:	afb200b0 	sw	s2,176(sp)
  400120:	afb100ac 	sw	s1,172(sp)
  400124:	afb000a8 	sw	s0,168(sp)
  400128:	afbf00b8 	sw	ra,184(sp)
  40012c:	246203e0 	addiu	v0,v1,992
  400130:	8c6403e0 	lw	a0,992(v1)
  400134:	8c480014 	lw	t0,20(v0)
  400138:	8c450004 	lw	a1,4(v0)
  40013c:	8c430008 	lw	v1,8(v0)
  400140:	8c46000c 	lw	a2,12(v0)
  400144:	8c470010 	lw	a3,16(v0)
  400148:	afa40010 	sw	a0,16(sp)
  40014c:	afa50014 	sw	a1,20(sp)
  400150:	afa30018 	sw	v1,24(sp)
  400154:	afa6001c 	sw	a2,28(sp)
  400158:	afa70020 	sw	a3,32(sp)
  40015c:	afa80024 	sw	t0,36(sp)
  400160:	27b20028 	addiu	s2,sp,40
  400164:	3c130040 	lui	s3,0x40
  400168:	27b10010 	addiu	s1,sp,16
  40016c:	24100005 	li	s0,5
  400170:	8e250000 	lw	a1,0(s1)
  400174:	0c100094 	jal	400250 <strcat>
  400178:	02402021 	move	a0,s2
  40017c:	0c1000b8 	jal	4002e0 <strlen>
  400180:	02402021 	move	a0,s2
  400184:	00403021 	move	a2,v0
  400188:	24040001 	li	a0,1
  40018c:	0c100088 	jal	400220 <__libc_write>
  400190:	02402821 	move	a1,s2
  400194:	2610ffff 	addiu	s0,s0,-1
  400198:	24040001 	li	a0,1
  40019c:	266503dc 	addiu	a1,s3,988
  4001a0:	0c100088 	jal	400220 <__libc_write>
  4001a4:	24060001 	li	a2,1
  4001a8:	0601fff1 	bgez	s0,400170 <main+0x60>
  4001ac:	26310004 	addiu	s1,s1,4
  4001b0:	8fbf00b8 	lw	ra,184(sp)
  4001b4:	8fb300b4 	lw	s3,180(sp)
  4001b8:	8fb200b0 	lw	s2,176(sp)
  4001bc:	8fb100ac 	lw	s1,172(sp)
  4001c0:	8fb000a8 	lw	s0,168(sp)
  4001c4:	00001021 	move	v0,zero
  4001c8:	03e00008 	jr	ra
  4001cc:	27bd00c0 	addiu	sp,sp,192

004001d0 <_exit>:
  4001d0:	24020fa1 	li	v0,4001
  4001d4:	0000000c 	syscall

004001d8 <__unified_syscall>:
  4001d8:	14e00003 	bnez	a3,4001e8 <error_unified_syscall>
  4001dc:	00000000 	nop

004001e0 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  4001e0:	03e00008 	jr	ra
  4001e4:	00000000 	nop

004001e8 <error_unified_syscall>:
  4001e8:	27bdffe8 	addiu	sp,sp,-24
  4001ec:	afbf0000 	sw	ra,0(sp)
  4001f0:	afa20004 	sw	v0,4(sp)
  4001f4:	3c190040 	lui	t9,0x40
  4001f8:	27390240 	addiu	t9,t9,576
  4001fc:	0320f809 	jalr	t9
  400200:	00000000 	nop
  400204:	8fa80004 	lw	t0,4(sp)
  400208:	8fbf0000 	lw	ra,0(sp)
  40020c:	ac480000 	sw	t0,0(v0)
  400210:	2402ffff 	li	v0,-1
  400214:	03e00008 	jr	ra
  400218:	27bd0018 	addiu	sp,sp,24
  40021c:	00000000 	nop

00400220 <__libc_write>:
  400220:	24020fa4 	li	v0,4004
  400224:	0000000c 	syscall
  400228:	3c190040 	lui	t9,0x40
  40022c:	273901d8 	addiu	t9,t9,472
  400230:	03200008 	jr	t9
  400234:	00000000 	nop
	...

00400240 <__errno_location>:
  400240:	3c021000 	lui	v0,0x1000
  400244:	03e00008 	jr	ra
  400248:	24420100 	addiu	v0,v0,256
  40024c:	00000000 	nop

00400250 <strcat>:
  400250:	27bdffe0 	addiu	sp,sp,-32
  400254:	afb10014 	sw	s1,20(sp)
  400258:	afb00010 	sw	s0,16(sp)
  40025c:	afbf0018 	sw	ra,24(sp)
  400260:	00808821 	move	s1,a0
  400264:	0c1000b8 	jal	4002e0 <strlen>
  400268:	00a08021 	move	s0,a1
  40026c:	02221821 	addu	v1,s1,v0
  400270:	92020000 	lbu	v0,0(s0)
  400274:	26100001 	addiu	s0,s0,1
  400278:	a0620000 	sb	v0,0(v1)
  40027c:	10400010 	beqz	v0,4002c0 <strcat+0x70>
  400280:	24630001 	addiu	v1,v1,1
  400284:	92020000 	lbu	v0,0(s0)
  400288:	26100001 	addiu	s0,s0,1
  40028c:	a0620000 	sb	v0,0(v1)
  400290:	1040000b 	beqz	v0,4002c0 <strcat+0x70>
  400294:	24630001 	addiu	v1,v1,1
  400298:	92020000 	lbu	v0,0(s0)
  40029c:	26100001 	addiu	s0,s0,1
  4002a0:	a0620000 	sb	v0,0(v1)
  4002a4:	10400006 	beqz	v0,4002c0 <strcat+0x70>
  4002a8:	24630001 	addiu	v1,v1,1
  4002ac:	92020000 	lbu	v0,0(s0)
  4002b0:	26100001 	addiu	s0,s0,1
  4002b4:	a0620000 	sb	v0,0(v1)
  4002b8:	1440ffed 	bnez	v0,400270 <strcat+0x20>
  4002bc:	24630001 	addiu	v1,v1,1
  4002c0:	02201021 	move	v0,s1
  4002c4:	8fbf0018 	lw	ra,24(sp)
  4002c8:	8fb10014 	lw	s1,20(sp)
  4002cc:	8fb00010 	lw	s0,16(sp)
  4002d0:	03e00008 	jr	ra
  4002d4:	27bd0020 	addiu	sp,sp,32
	...

004002e0 <strlen>:
  4002e0:	27bdfff8 	addiu	sp,sp,-8
  4002e4:	00803021 	move	a2,a0
  4002e8:	10800025 	beqz	a0,400380 <strlen+0xa0>
  4002ec:	00001021 	move	v0,zero
  4002f0:	081000c0 	j	400300 <strlen+0x20>
  4002f4:	30820003 	andi	v0,a0,0x3
  4002f8:	081000e0 	j	400380 <strlen+0xa0>
  4002fc:	00c41023 	subu	v0,a2,a0
  400300:	10400008 	beqz	v0,400324 <strlen+0x44>
  400304:	00000000 	nop
  400308:	80c20000 	lb	v0,0(a2)
  40030c:	00000000 	nop
  400310:	1040fff9 	beqz	v0,4002f8 <strlen+0x18>
  400314:	00000000 	nop
  400318:	24c60001 	addiu	a2,a2,1
  40031c:	081000c0 	j	400300 <strlen+0x20>
  400320:	30c20003 	andi	v0,a2,0x3
  400324:	8cc50000 	lw	a1,0(a2)
  400328:	3c02fefe 	lui	v0,0xfefe
  40032c:	3442feff 	ori	v0,v0,0xfeff
  400330:	00a21021 	addu	v0,a1,v0
  400334:	00051827 	nor	v1,zero,a1
  400338:	00432824 	and	a1,v0,v1
  40033c:	3c028080 	lui	v0,0x8080
  400340:	34428080 	ori	v0,v0,0x8080
  400344:	00a22824 	and	a1,a1,v0
  400348:	10a0fff6 	beqz	a1,400324 <strlen+0x44>
  40034c:	24c60004 	addiu	a2,a2,4
  400350:	3c020404 	lui	v0,0x404
  400354:	24a3ffff 	addiu	v1,a1,-1
  400358:	34420400 	ori	v0,v0,0x400
  40035c:	00622824 	and	a1,v1,v0
  400360:	00051200 	sll	v0,a1,0x8
  400364:	00051c00 	sll	v1,a1,0x10
  400368:	00431021 	addu	v0,v0,v1
  40036c:	00a22821 	addu	a1,a1,v0
  400370:	00051682 	srl	v0,a1,0x1a
  400374:	00c23021 	addu	a2,a2,v0
  400378:	00c41023 	subu	v0,a2,a0
  40037c:	2442fffc 	addiu	v0,v0,-4
  400380:	03e00008 	jr	ra
  400384:	27bd0008 	addiu	sp,sp,8
	...

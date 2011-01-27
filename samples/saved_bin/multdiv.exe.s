
multdiv:     file format elf32-tradlittlemips

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
  4000e0:	2739012c 	addiu	t9,t9,300
  4000e4:	00c53020 	add	a2,a2,a1
  4000e8:	3c011000 	lui	at,0x1000
  4000ec:	0320f809 	jalr	t9
  4000f0:	ac260000 	sw	a2,0(at)
  4000f4:	3c190040 	lui	t9,0x40
  4000f8:	27390180 	addiu	t9,t9,384
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <mydiv>:
  400110:	0085001a 	div	zero,a0,a1
  400114:	14a00002 	bnez	a1,400120 <mydiv+0x10>
  400118:	00000000 	nop
  40011c:	0007000d 	break	0x7
  400120:	00001012 	mflo	v0
  400124:	03e00008 	jr	ra
  400128:	00000000 	nop

0040012c <main>:
  40012c:	27bdffc8 	addiu	sp,sp,-56
  400130:	afbf0030 	sw	ra,48(sp)
  400134:	8ca20004 	lw	v0,4(a1)
  400138:	8ca30008 	lw	v1,8(a1)
  40013c:	00402021 	move	a0,v0
  400140:	afa30014 	sw	v1,20(sp)
  400144:	afa3001c 	sw	v1,28(sp)
  400148:	afa20018 	sw	v0,24(sp)
  40014c:	0c100074 	jal	4001d0 <atoi>
  400150:	afa20010 	sw	v0,16(sp)
  400154:	8fa40014 	lw	a0,20(sp)
  400158:	0c100074 	jal	4001d0 <atoi>
  40015c:	afa20028 	sw	v0,40(sp)
  400160:	8fa40028 	lw	a0,40(sp)
  400164:	0c100044 	jal	400110 <mydiv>
  400168:	00402821 	move	a1,v0
  40016c:	8fbf0030 	lw	ra,48(sp)
  400170:	00000000 	nop
  400174:	03e00008 	jr	ra
  400178:	27bd0038 	addiu	sp,sp,56
  40017c:	00000000 	nop

00400180 <_exit>:
  400180:	24020fa1 	li	v0,4001
  400184:	0000000c 	syscall

00400188 <__unified_syscall>:
  400188:	14e00003 	bnez	a3,400198 <error_unified_syscall>
  40018c:	00000000 	nop

00400190 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  400190:	03e00008 	jr	ra
  400194:	00000000 	nop

00400198 <error_unified_syscall>:
  400198:	27bdffe8 	addiu	sp,sp,-24
  40019c:	afbf0000 	sw	ra,0(sp)
  4001a0:	afa20004 	sw	v0,4(sp)
  4001a4:	3c190040 	lui	t9,0x40
  4001a8:	27390290 	addiu	t9,t9,656
  4001ac:	0320f809 	jalr	t9
  4001b0:	00000000 	nop
  4001b4:	8fa80004 	lw	t0,4(sp)
  4001b8:	8fbf0000 	lw	ra,0(sp)
  4001bc:	ac480000 	sw	t0,0(v0)
  4001c0:	2402ffff 	li	v0,-1
  4001c4:	03e00008 	jr	ra
  4001c8:	27bd0018 	addiu	sp,sp,24
  4001cc:	00000000 	nop

004001d0 <atoi>:
  4001d0:	80830000 	lb	v1,0(a0)
  4001d4:	24020020 	li	v0,32
  4001d8:	00002821 	move	a1,zero
  4001dc:	10620005 	beq	v1,v0,4001f4 <atoi+0x24>
  4001e0:	00003821 	move	a3,zero
  4001e4:	2462fff7 	addiu	v0,v1,-9
  4001e8:	2c420005 	sltiu	v0,v0,5
  4001ec:	1040000c 	beqz	v0,400220 <atoi+0x50>
  4001f0:	00000000 	nop
  4001f4:	24060020 	li	a2,32
  4001f8:	24840001 	addiu	a0,a0,1
  4001fc:	80830000 	lb	v1,0(a0)
  400200:	00000000 	nop
  400204:	2462fff7 	addiu	v0,v1,-9
  400208:	1066fffb 	beq	v1,a2,4001f8 <atoi+0x28>
  40020c:	2c420005 	sltiu	v0,v0,5
  400210:	1440fffa 	bnez	v0,4001fc <atoi+0x2c>
  400214:	24840001 	addiu	a0,a0,1
  400218:	2484ffff 	addiu	a0,a0,-1
  40021c:	80830000 	lb	v1,0(a0)
  400220:	2402002b 	li	v0,43
  400224:	10620004 	beq	v1,v0,400238 <atoi+0x68>
  400228:	2402002d 	li	v0,45
  40022c:	14620003 	bne	v1,v0,40023c <atoi+0x6c>
  400230:	00000000 	nop
  400234:	2407ffff 	li	a3,-1
  400238:	24840001 	addiu	a0,a0,1
  40023c:	80830000 	lb	v1,0(a0)
  400240:	00000000 	nop
  400244:	2462ffd0 	addiu	v0,v1,-48
  400248:	2c42000a 	sltiu	v0,v0,10
  40024c:	10400008 	beqz	v0,400270 <atoi+0xa0>
  400250:	00051080 	sll	v0,a1,0x2
  400254:	00451021 	addu	v0,v0,a1
  400258:	00021040 	sll	v0,v0,0x1
  40025c:	24840001 	addiu	a0,a0,1
  400260:	00431021 	addu	v0,v0,v1
  400264:	80830000 	lb	v1,0(a0)
  400268:	08100091 	j	400244 <atoi+0x74>
  40026c:	2445ffd0 	addiu	a1,v0,-48
  400270:	10e00002 	beqz	a3,40027c <atoi+0xac>
  400274:	00a01021 	move	v0,a1
  400278:	00051023 	negu	v0,a1
  40027c:	03e00008 	jr	ra
  400280:	00000000 	nop
	...

00400290 <__errno_location>:
  400290:	3c021000 	lui	v0,0x1000
  400294:	03e00008 	jr	ra
  400298:	24420100 	addiu	v0,v0,256
  40029c:	00000000 	nop

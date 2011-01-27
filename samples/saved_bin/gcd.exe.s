
gcd:     file format elf32-tradlittlemips

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
  4000e0:	27390144 	addiu	t9,t9,324
  4000e4:	00c53020 	add	a2,a2,a1
  4000e8:	3c011000 	lui	at,0x1000
  4000ec:	0320f809 	jalr	t9
  4000f0:	ac260000 	sw	a2,0(at)
  4000f4:	3c190040 	lui	t9,0x40
  4000f8:	273901a0 	addiu	t9,t9,416
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <gcd>:
  400110:	10a0000a 	beqz	a1,40013c <gcd+0x2c>
  400114:	00a01021 	move	v0,a1
  400118:	0082001a 	div	zero,a0,v0
  40011c:	14400002 	bnez	v0,400128 <gcd+0x18>
  400120:	00000000 	nop
  400124:	0007000d 	break	0x7
  400128:	00402021 	move	a0,v0
  40012c:	00001810 	mfhi	v1
  400130:	00001010 	mfhi	v0
  400134:	1460fff8 	bnez	v1,400118 <gcd+0x8>
  400138:	00000000 	nop
  40013c:	03e00008 	jr	ra
  400140:	00801021 	move	v0,a0

00400144 <main>:
  400144:	27bdffd8 	addiu	sp,sp,-40
  400148:	afbf0024 	sw	ra,36(sp)
  40014c:	afb00020 	sw	s0,32(sp)
  400150:	8ca20004 	lw	v0,4(a1)
  400154:	8ca30008 	lw	v1,8(a1)
  400158:	00402021 	move	a0,v0
  40015c:	afa30014 	sw	v1,20(sp)
  400160:	afa3001c 	sw	v1,28(sp)
  400164:	afa20018 	sw	v0,24(sp)
  400168:	0c10007c 	jal	4001f0 <atoi>
  40016c:	afa20010 	sw	v0,16(sp)
  400170:	8fa40014 	lw	a0,20(sp)
  400174:	0c10007c 	jal	4001f0 <atoi>
  400178:	00408021 	move	s0,v0
  40017c:	00402821 	move	a1,v0
  400180:	0c100044 	jal	400110 <gcd>
  400184:	02002021 	move	a0,s0
  400188:	8fbf0024 	lw	ra,36(sp)
  40018c:	8fb00020 	lw	s0,32(sp)
  400190:	03e00008 	jr	ra
  400194:	27bd0028 	addiu	sp,sp,40
	...

004001a0 <_exit>:
  4001a0:	24020fa1 	li	v0,4001
  4001a4:	0000000c 	syscall

004001a8 <__unified_syscall>:
  4001a8:	14e00003 	bnez	a3,4001b8 <error_unified_syscall>
  4001ac:	00000000 	nop

004001b0 <__you_tried_to_link_a_dietlibc_object_against_glibc>:
  4001b0:	03e00008 	jr	ra
  4001b4:	00000000 	nop

004001b8 <error_unified_syscall>:
  4001b8:	27bdffe8 	addiu	sp,sp,-24
  4001bc:	afbf0000 	sw	ra,0(sp)
  4001c0:	afa20004 	sw	v0,4(sp)
  4001c4:	3c190040 	lui	t9,0x40
  4001c8:	273902b0 	addiu	t9,t9,688
  4001cc:	0320f809 	jalr	t9
  4001d0:	00000000 	nop
  4001d4:	8fa80004 	lw	t0,4(sp)
  4001d8:	8fbf0000 	lw	ra,0(sp)
  4001dc:	ac480000 	sw	t0,0(v0)
  4001e0:	2402ffff 	li	v0,-1
  4001e4:	03e00008 	jr	ra
  4001e8:	27bd0018 	addiu	sp,sp,24
  4001ec:	00000000 	nop

004001f0 <atoi>:
  4001f0:	80830000 	lb	v1,0(a0)
  4001f4:	24020020 	li	v0,32
  4001f8:	00002821 	move	a1,zero
  4001fc:	10620005 	beq	v1,v0,400214 <atoi+0x24>
  400200:	00003821 	move	a3,zero
  400204:	2462fff7 	addiu	v0,v1,-9
  400208:	2c420005 	sltiu	v0,v0,5
  40020c:	1040000c 	beqz	v0,400240 <atoi+0x50>
  400210:	00000000 	nop
  400214:	24060020 	li	a2,32
  400218:	24840001 	addiu	a0,a0,1
  40021c:	80830000 	lb	v1,0(a0)
  400220:	00000000 	nop
  400224:	2462fff7 	addiu	v0,v1,-9
  400228:	1066fffb 	beq	v1,a2,400218 <atoi+0x28>
  40022c:	2c420005 	sltiu	v0,v0,5
  400230:	1440fffa 	bnez	v0,40021c <atoi+0x2c>
  400234:	24840001 	addiu	a0,a0,1
  400238:	2484ffff 	addiu	a0,a0,-1
  40023c:	80830000 	lb	v1,0(a0)
  400240:	2402002b 	li	v0,43
  400244:	10620004 	beq	v1,v0,400258 <atoi+0x68>
  400248:	2402002d 	li	v0,45
  40024c:	14620003 	bne	v1,v0,40025c <atoi+0x6c>
  400250:	00000000 	nop
  400254:	2407ffff 	li	a3,-1
  400258:	24840001 	addiu	a0,a0,1
  40025c:	80830000 	lb	v1,0(a0)
  400260:	00000000 	nop
  400264:	2462ffd0 	addiu	v0,v1,-48
  400268:	2c42000a 	sltiu	v0,v0,10
  40026c:	10400008 	beqz	v0,400290 <atoi+0xa0>
  400270:	00051080 	sll	v0,a1,0x2
  400274:	00451021 	addu	v0,v0,a1
  400278:	00021040 	sll	v0,v0,0x1
  40027c:	24840001 	addiu	a0,a0,1
  400280:	00431021 	addu	v0,v0,v1
  400284:	80830000 	lb	v1,0(a0)
  400288:	08100099 	j	400264 <atoi+0x74>
  40028c:	2445ffd0 	addiu	a1,v0,-48
  400290:	10e00002 	beqz	a3,40029c <atoi+0xac>
  400294:	00a01021 	move	v0,a1
  400298:	00051023 	negu	v0,a1
  40029c:	03e00008 	jr	ra
  4002a0:	00000000 	nop
	...

004002b0 <__errno_location>:
  4002b0:	3c021000 	lui	v0,0x1000
  4002b4:	03e00008 	jr	ra
  4002b8:	24420100 	addiu	v0,v0,256
  4002bc:	00000000 	nop

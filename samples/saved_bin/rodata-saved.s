
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
  4000f8:	27390180 	addiu	t9,t9,384
  4000fc:	0320f809 	jalr	t9
  400100:	00402021 	move	a0,v0

00400104 <__main>:
  400104:	03e00008 	jr	ra
  400108:	00000000 	nop
  40010c:	00000000 	nop

00400110 <main>:
  400110:	27bdffe0 	addiu	sp,sp,-32
  400114:	afbf001c 	sw	ra,28(sp)
  400118:	afbe0018 	sw	s8,24(sp)
  40011c:	03a0f021 	move	s8,sp
  400120:	3c030040 	lui	v1,0x40
the half-word 'ku' from rodata:
  400124:	946202b0 	lhu	v0,688(v1)
  400128:	00000000 	nop
and save to stack, at addr
mem_write_bytes vaddr=0x7fffffb8, phys addr=0x203c8 len=2    
  40012c:	a7c20010 	sh	v0,16(s8)
  400130:	246202b0 	addiu	v0,v1,688
string terminator '\0':
  400134:	90420002 	lbu	v0,2(v0)
  400138:	00000000 	nop
store null terminator:
mem_write_bytes vaddr=0x7fffffba, phys addr=0x203ca len=1    
  40013c:	a3c20012 	sb	v0,18(s8)
  400140:	27c40010 	addiu	a0,s8,16
  400144:	0c100080 	jal	400200 <strlen>
  400148:	00000000 	nop
  40014c:	24040001 	li	a0,1
  400150:	27c50010 	addiu	a1,s8,16
  400154:	00403021 	move	a2,v0
  400158:	0c100074 	jal	4001d0 <__libc_write>
  40015c:	00000000 	nop
  400160:	00001021 	move	v0,zero
  400164:	03c0e821 	move	sp,s8
  400168:	8fbf001c 	lw	ra,28(sp)
  40016c:	8fbe0018 	lw	s8,24(sp)
  400170:	27bd0020 	addiu	sp,sp,32
  400174:	03e00008 	jr	ra
  400178:	00000000 	nop
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
  4001a8:	273901f0 	addiu	t9,t9,496
  4001ac:	0320f809 	jalr	t9
  4001b0:	00000000 	nop
  4001b4:	8fa80004 	lw	t0,4(sp)
  4001b8:	8fbf0000 	lw	ra,0(sp)
  4001bc:	ac480000 	sw	t0,0(v0)
  4001c0:	2402ffff 	li	v0,-1
  4001c4:	03e00008 	jr	ra
  4001c8:	27bd0018 	addiu	sp,sp,24
  4001cc:	00000000 	nop

004001d0 <__libc_write>:
  4001d0:	24020fa4 	li	v0,4004
  4001d4:	0000000c 	syscall
  4001d8:	3c190040 	lui	t9,0x40
  4001dc:	27390188 	addiu	t9,t9,392
  4001e0:	03200008 	jr	t9
  4001e4:	00000000 	nop
	...

004001f0 <__errno_location>:
  4001f0:	3c021000 	lui	v0,0x1000
  4001f4:	03e00008 	jr	ra
  4001f8:	24420100 	addiu	v0,v0,256
  4001fc:	00000000 	nop

00400200 <strlen>:
  400200:	27bdfff8 	addiu	sp,sp,-8
  400204:	00803021 	move	a2,a0
  400208:	10800025 	beqz	a0,4002a0 <strlen+0xa0>
  40020c:	00001021 	move	v0,zero
  400210:	08100088 	j	400220 <strlen+0x20>
  400214:	30820003 	andi	v0,a0,0x3
return
  400218:	081000a8 	j	4002a0 <strlen+0xa0>
  40021c:	00c41023 	subu	v0,a2,a0
start of pre-word loop
end loop (while ... do ...)
  400220:	10400008 	beqz	v0,400244 <strlen+0x44>
  400224:	00000000 	nop
  400228:	80c20000 	lb	v0,0(a2)
  40022c:	00000000 	nop
this goes to return
  400230:	1040fff9 	beqz	v0,400218 <strlen+0x18>
  400234:	00000000 	nop
  400238:	24c60001 	addiu	a2,a2,1
end of pre-word loop
  40023c:	08100088 	j	400220 <strlen+0x20>
  400240:	30c20003 	andi	v0,a2,0x3
start of word-count loop
the failing lw:
  400244:	8cc50000 	lw	a1,0(a2)
  400248:	3c02fefe 	lui	v0,0xfefe
  40024c:	3442feff 	ori	v0,v0,0xfeff
  400250:	00a21021 	addu	v0,a1,v0
  400254:	00051827 	nor	v1,zero,a1
  400258:	00432824 	and	a1,v0,v1
  40025c:	3c028080 	lui	v0,0x8080
  400260:	34428080 	ori	v0,v0,0x8080
  400264:	00a22824 	and	a1,a1,v0
end of loop, jumps back to the failing lw:
  400268:	10a0fff6 	beqz	a1,400244 <strlen+0x44>
increments the addr given to the failing lw
  40026c:	24c60004 	addiu	a2,a2,4
and now the post-word boundary cleanup
  400270:	3c020404 	lui	v0,0x404
  400274:	24a3ffff 	addiu	v1,a1,-1
  400278:	34420400 	ori	v0,v0,0x400
  40027c:	00622824 	and	a1,v1,v0
  400280:	00051200 	sll	v0,a1,0x8
  400284:	00051c00 	sll	v1,a1,0x10
  400288:	00431021 	addu	v0,v0,v1
  40028c:	00a22821 	addu	a1,a1,v0
  400290:	00051682 	srl	v0,a1,0x1a
  400294:	00c23021 	addu	a2,a2,v0
  400298:	00c41023 	subu	v0,a2,a0
  40029c:	2442fffc 	addiu	v0,v0,-4
  4002a0:	03e00008 	jr	ra
  4002a4:	27bd0008 	addiu	sp,sp,8
	...

  /* Start.s
 *	Assembly language assist for user programs running on top of Nachos.
 *
 *	Since we don't want to pull in the entire C library, we define
 *	what we need for a user program here, namely Start and the system
 *	calls.
 */

#include "syscall.h"

        .text
        .align  2

/* -------------------------------------------------------------
 * __start
 *	Initialize running a C program, by calling "main".
 *
 * 	NOTE: This has to be first, so that it gets loaded at location 0.
 *	The Nachos kernel always starts a program by jumping to location 0.
 * -------------------------------------------------------------
 */

	.globl __start
	.ent	__start
__start:
	jal	main
	move	$4,$2
	jal	Exit	 /* if we return from main, exit(0) */
	.end __start

/* -------------------------------------------------------------
 * System call stubs:
 *	Assembly language assist to make system calls to the Nachos kernel.
 *	There is one stub per system call, that places the code for the
 *	system call into register r2, and leaves the arguments to the
 *	system call alone (in other words, arg1 is in r4, arg2 is
 *	in r5, arg3 is in r6, arg4 is in r7)
 *
 * 	The return value is in r2. This follows the standard C calling
 * 	convention on the MIPS.
 * -------------------------------------------------------------
 */

	.globl Halt
	.ent	Halt
Halt:
	addiu $2,$0,SC_Halt
	syscall
	j	$31
	.end Halt

	.globl Exit
	.ent	Exit
Exit:
	addiu $2,$0,SC_Exit
	syscall
	j	$31
	.end Exit

	.globl Exec
	.ent	Exec
Exec:
	addiu $2,$0,SC_Exec
	syscall
	j	$31
	.end Exec

	.globl Join
	.ent	Join
Join:
	addiu $2,$0,SC_Join
	syscall
	j	$31
	.end Join

	.globl Create
	.ent	Create
Create:
	addiu $2,$0,SC_Create
	syscall
	j	$31
	.end Create

	.globl Open
	.ent	Open
Open:
	addiu $2,$0,SC_Open
	syscall
	j	$31
	.end Open

	.globl Read
	.ent	Read
Read:
	addiu $2,$0,SC_Read
	syscall
	j	$31
	.end Read

	.globl Write
	.ent	Write
Write:
	addiu $2,$0,SC_Write
	syscall
	j	$31
	.end Write

	.globl Close
	.ent	Close
Close:
	addiu $2,$0,SC_Close
	syscall
	j	$31
	.end Close

	.globl Fork
	.ent	Fork
Fork:
	addiu $2,$0,SC_Fork
	syscall
	j	$31
	.end Fork

	.globl Yield
	.ent	Yield
Yield:
	addiu $2,$0,SC_Yield
	syscall
	j	$31
	.end Yield

  .globl PutChar
  .ent PutChar
PutChar:
  addiu $2,$0,SC_PutChar
  syscall
  j	$31
  .end PutChar

  .globl SynchPutString
  .ent SynchPutString
SynchPutString:
  addiu $2,$0,SC_SynchPutString
  syscall
  j	$31
  .end SynchPutString

  .globl SynchGetChar
  .ent SynchGetChar
SynchGetChar:
  addiu $2,$0,SC_SynchGetChar
  syscall
  j	$31
  .end SynchGetChar

  .globl SynchGetString
  .ent SynchGetString
SynchGetString:
  addiu $2,$0,SC_SynchGetString
  syscall
  j	$31
  .end SynchGetString

  .globl SynchGetInt
  .ent SynchGetInt
SynchGetInt:
  addiu $2,$0,SC_SynchGetInt
  syscall
  j	$31
  .end SynchGetInt

  .globl SynchPutInt
  .ent SynchPutInt
SynchPutInt:
  addiu $2,$0,SC_SynchPutInt
  syscall
  j	$31
  .end SynchPutInt

  .globl UserThreadCreate
  .ent UserThreadCreate
UserThreadCreate:
  addiu $2,$0,SC_UserThreadCreate
  syscall
  j	$31
  .end UserThreadCreate

  .globl UserThreadExit
  .ent UserThreadExit
UserThreadExit:
  addiu $2,$0,SC_UserThreadExit
  syscall
  j	$31
  .end UserThreadExit

  .globl UserThreadJoin
  .ent UserThreadJoin
UserThreadJoin:
  addiu $2,$0,SC_UserThreadJoin
  syscall
  j	$31
  .end UserThreadJoin

  .globl ForkExec
  .ent ForkExec
ForkExec:
  addiu $2,$0,SC_ForkExec
  syscall
  j	$31
  .end ForkExec

  .globl UserSemaphore
  .ent UserSemaphore
UserSemaphore:
  addiu $2,$0,SC_UserSemaphore
  syscall
  j	$31
  .end UserSemaphore

  .globl V
  .ent V

  .globl P
  .ent P
P:
  addiu $2,$0,SC_P
  syscall
  j	$31
  .end P

  .globl V
  .ent V


V:
  addiu $2,$0,SC_V
  syscall
  j	$31
  .end V


  .globl AddDir
  .ent AddDir
AddDir:
  addiu $2,$0,SC_AddDir
	syscall
	j	$31
  .end AddDir

  .globl ChangeDir
  .ent ChangeDir
ChangeDir:
  addiu $2,$0,SC_ChangeDir
  syscall
  j	$31
  .end ChangeDir
 
  .globl AllocEmptyPage
  .ent AllocEmptyPage
AllocEmptyPage:
  addiu $2,$0, SC_AllocEmptyPage
  syscall
  j	$31
.end AllocEmptyPage

  .globl Sbrk
  .ent Sbrk
Sbrk:
	  addiu $2,$0, SC_Sbrk
	  syscall
	  j	$31
	.end Sbrk



/* dummy function to keep gcc happy */
        .globl  __main
        .ent    __main
__main:
        j       $31
        .end    __main

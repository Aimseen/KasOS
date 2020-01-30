// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"
#include "synch.h"
#include "usersynch.h"

static Semaphore *verrouxProcess=new Semaphore("eee",1);
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


void copyStringFromMachine(int from, char *to, unsigned size){
  if (size>MAX_STRING_SIZE){
    size = MAX_STRING_SIZE;
  }
  for(unsigned i=0; i<size; i++){
    machine->ReadMem(from+i, 1, (int*)(to+i));
  }
  *(to+size) = '\0';
}

//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------
extern void StartProcess (char *filename);

void forkIntermedaire(int parametre){
  StartProcess ((char*)parametre);
}
void ExceptionHandler(ExceptionType which){
  int type = machine->ReadRegister(2);
  if (which == SyscallException) {
    switch (type) {
      case SC_Halt: {
        DEBUG('a', "Shutdown, initiated by user program.\n");
        printf("%s\n","halt" );
        interrupt->Halt();
        break;
      }
      case SC_Exit: {
        printf("%s\n","exit" );
        DEBUG('a', "Shutdown, initiated by user program.\n");
        verrouxProcess->P();
        if(nbProcessus==1){
          verrouxProcess->V();
          interrupt->Halt();
        }else{
          nbProcessus--;
          verrouxProcess->V();
          delete currentThread->space;
          currentThread->Finish();
        }
        //interrupt->Halt();
        break;
      }
      case SC_PutChar: {
        synchconsole->SynchPutChar((char) machine->ReadRegister(4));
        break;
      }
      case SC_SynchPutString: {
        unsigned size = (unsigned) machine->ReadRegister(5);
        char s[size+1];
        copyStringFromMachine(machine->ReadRegister(4), s, size);
        synchconsole->SynchPutString(s);
        break;
      }
      case SC_SynchGetChar: {
        machine->WriteRegister(2, (int) synchconsole->SynchGetChar());
        break;
      }
      case SC_SynchGetString: {
        int tmp=-1;
        machine->Translate(machine->ReadRegister(4),&tmp,4,TRUE);
        synchconsole->SynchGetString((char*)&machine->mainMemory[tmp], machine->ReadRegister(5));
        break;
      }
      case SC_SynchGetInt: {
        int tmp=-1;
        machine->Translate(machine->ReadRegister(4),&tmp,4,TRUE);
        synchconsole->SynchGetInt((int*)&machine->mainMemory[tmp]);
        break;
      }
      case SC_SynchPutInt: {
        synchconsole->SynchPutInt(machine->ReadRegister(4));
        break;
      }
      case SC_UserThreadCreate: {
        machine->WriteRegister(2,do_UserThreadCreate(machine->ReadRegister(4), machine->ReadRegister(5)));
        break;
      }
      case SC_UserThreadExit: {
        do_UserThreadExit();
        break;
      }case SC_UserThreadJoin: {
        do_UserThreadJoin(machine->ReadRegister(4));
        break;
      }
      case SC_ForkExec: {
        char* string=(char*)malloc(MAX_STRING_SIZE*sizeof(char));
        copyStringFromMachine(machine->ReadRegister(4), string, MAX_STRING_SIZE);
        /*int tmp=-1;
        machine->Translate(machine->ReadRegister(4),&tmp,4,TRUE);
        char* string=(char*)&machine->mainMemory[tmp];*/
        //printf("%s\n",string);
        verrouxProcess->P();
        nbProcessus++;
        verrouxProcess->V();
        Thread * t =new Thread(string);
        t->Fork(&forkIntermedaire,(int)string);
        break;
      }
      case SC_UserSemaphore: {//semaphoreLibre/tabSemaphore
        char* string=(char*)malloc(MAX_STRING_SIZE*sizeof(char));
        copyStringFromMachine(machine->ReadRegister(4), string, MAX_STRING_SIZE);
        int idSema=currentThread->space->semaphoreLibre->Find();
        currentThread->space->tabSemaphore[idSema]=new Semaphore(string,machine->ReadRegister(5));
        //printf("%d\n",(int)ret );
        machine->WriteRegister(2,idSema);
        break;
      }
      case SC_P: {
        //printf("%d\n", machine->ReadRegister(4));
        currentThread->space->tabSemaphore[machine->ReadRegister(4)]->P();
        break;
      }
      case SC_V: {
        //printf("%d\n", machine->ReadRegister(4));
        currentThread->space->tabSemaphore[machine->ReadRegister(4)]->V();
        break;
      }
      default: {
        printf("Unexpected user mode exception %d %d\n", which, type);
        ASSERT(FALSE);
      }
    }
    UpdatePC();
  }
}

// progtest.cc
//      Test routines for demonstrating that Nachos can load
//      a user program and execute it.
//
//      Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "synch.h"
#include "synchconsole.h"

//----------------------------------------------------------------------
// StartProcess
//      Run a user program.  Open the executable, load it into
//      memory, and jump to it.
//----------------------------------------------------------------------

void
StartProcess (char *filename)
{
    OpenFile *executable = fileSystem->Open (filename);
    AddrSpace *space;

    if (executable == NULL)
      {
	  printf ("Unable to open file %s\n", filename);
	  return;
      }
    space = new AddrSpace (executable);
    currentThread->space = space;

    delete executable;		// close file

    space->InitRegisters ();	// set the initial register values
    space->RestoreState ();	// load page table register
    machine->Run ();		// jump to the user progam
    ASSERT (FALSE);		// machine->Run never returns;
    // the address space exits
    // by doing the syscall "exit"
}

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
//      Wake up the thread that requested the I/O.
//----------------------------------------------------------------------



//----------------------------------------------------------------------
// ConsoleTest
//      Test the console by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void
ConsoleTest (char *in, char *out)
{
    char ch;

    synchconsole = new SynchConsole (in, out);

    for (;;){
  	  ch = synchconsole->SynchGetChar();
  	  synchconsole->SynchPutChar(ch);	// echo it!
  	  if (ch == 'q' || ch == EOF){return;}		// if q, quit
    }
}

void SynchConsoleTest (char *in, char *out) {
  char ch;
  bool start = true;
  synchconsole = new SynchConsole(in, out);
  while ((ch = synchconsole->SynchGetChar()) != EOF){
  if (start){
    synchconsole->SynchPutChar('<');
    start = false;
  }
  if(ch == '\n'){
    synchconsole->SynchPutChar('>');
    start = true;
  }
  synchconsole->SynchPutChar(ch);
  if (ch == EOF){return;}		// if q, quit
}
  fprintf(stderr, "Solaris: EOF detected in SynchConsole!\n");
}

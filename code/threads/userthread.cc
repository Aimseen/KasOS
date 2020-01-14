#include "userthread.h"
#include "system.h"

static void StartUserThread(int farg){
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();
  int* tab = (int*) farg;
  machine->WriteRegister(PCReg, tab[0]);
  machine->WriteRegister(NextPCReg, tab[0] + 4);
  machine->WriteRegister(4, tab[1]);
  machine->Run();
  //UserThreadExit(); made by ThreadRoot?
}

void do_UserThreadExit(){
  delete currentThread->space;
  currentThread->Finish();
}

int do_UserThreadCreate(int f, int arg){
  Thread* newThread = new Thread("Unknow");
  int* farg = (int*) malloc(2* sizeof(int));
  farg[0]=f;
  farg[1]=arg;
  newThread->Fork(&StartUserThread, (int) farg);
  return 0;
}

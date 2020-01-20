#include "userthread.h"
#include "system.h"

static void StartUserThread(int farg){
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();

  int* tab = (int*) farg;
  machine->WriteRegister(PCReg, tab[0]);
  machine->WriteRegister(NextPCReg, tab[0] + 4);
  machine->WriteRegister(4, tab[1]);

      int t = (currentThread->bitMapNb+1)*(int)PageSize*(int)PagePerTheadStack - (int)UserStackSize + ((int)currentThread->space->numPages * (int)PageSize) - 16;
      //printf("test: %d\n",  (int)currentThread->space->numPages);
      //printf("create adresse: %d\n",  t);
      machine->WriteRegister(StackReg, t);
      currentThread->space->threads++;
      machine->Run();

}

void do_UserThreadExit(){
  //printf("exit adresse: %d\n",  machine->ReadRegister(StackReg));
  currentThread->space->bm->Clear(currentThread->bitMapNb);
  currentThread->space->threads--;//Ne devrait pas etre exécuté par le thread concerné
  currentThread->Finish();
}

int do_UserThreadCreate(int f, int arg){
  Thread* newThread = new Thread("Unknow");
  int* farg = (int*) malloc(2* sizeof(int));
  farg[0]=f;
  farg[1]=arg;
  newThread->bitMapNb = currentThread->space->bm->Find();
  if(newThread->bitMapNb == -1){
    delete newThread;
    printf("Thread échou a la creation, manque de mémoire\n");
    return -1;
  }
  newThread->Fork(&StartUserThread, (int) farg);
  return 0;
}

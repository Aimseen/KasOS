#include "userthread.h"
#include "system.h"

static void StartUserThread(int farg){
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();

  int* tab = (int*) farg;
  machine->WriteRegister(PCReg, tab[0]);
  machine->WriteRegister(NextPCReg, tab[0] + 4);
  machine->WriteRegister(4, tab[1]);
  int t=currentThread->space->bm->Find()*PageSize*2+16*2;//problemme dans la formule
  /*
  //vielle formulle
  currentThread->space->bm->Find()*PageSize*2-16;
  //probleme d'overflow
  //run :: ./nachos-step2 -s -rs -x programme
  //le registre sp : ffffffff au bout d'un moment 
  */
  printf("%d\n",t);
  machine->WriteRegister(StackReg, t);
  machine->Run();
   //Finish made by ThreadRoot?
}

void do_UserThreadExit(){
  currentThread->space->bm->Clear((machine->ReadRegister(StackReg)+16)/2/PageSize);
  currentThread->space->threads--;//Ne devrait pas etre exécuté par le thread concerné
  currentThread->Finish();
}

int do_UserThreadCreate(int f, int arg){
  Thread* newThread = new Thread("Unknow");
  int* farg = (int*) malloc(2* sizeof(int));
  farg[0]=f;
  farg[1]=arg;
  currentThread->space->threads++;
  newThread->Fork(&StartUserThread, (int) farg);
  return 0;
}

#include "userthread.h"
#include "system.h"

static void StartUserThread(int farg){
  currentThread->space->InitRegisters();
  currentThread->space->RestoreState();

  int* tab = (int*) farg;
  machine->WriteRegister(PCReg, tab[0]);
  machine->WriteRegister(NextPCReg, tab[0] + 4);
  machine->WriteRegister(4, tab[1]);
  int t = (currentThread->space->bm->Find()+1)*(int)PageSize*(int)PagePerTheadStack - (int)UserStackSize + ((int)currentThread->space->numPages * (int)PageSize) - 16;

  printf("create adresse: %d\n",  t);

  /*
  //vielle formulle
  currentThread->space->bm->Find()*PageSize*2-16;
  //probleme d'overflow
  //run :: ./nachos-step2 -s -rs -x programme
  //le registre sp : ffffffff au bout d'un moment
  */
  machine->WriteRegister(StackReg, t);
  machine->Run();
   //Finish made by ThreadRoot?
}

void do_UserThreadExit(){
  printf("exit adresse: %d\n",  machine->ReadRegister(StackReg));

  printf("clear: %d\n", (machine->ReadRegister(StackReg) + 16 + (int)UserStackSize - ((int)currentThread->space->numPages * (int)PageSize))/(int)PagePerTheadStack/(int)PageSize-1);
  currentThread->space->bm->Clear((machine->ReadRegister(StackReg) + 24 + 16 + (int)UserStackSize - ((int)currentThread->space->numPages * (int)PageSize))/(int)PagePerTheadStack/(int)PageSize-1);//?????? Formule surment fausse
  currentThread->space->threads--;//Ne devrait pas etre exécuté par le thread concerné
  currentThread->Finish();
}

int do_UserThreadCreate(int f, int arg){
  Thread* newThread = new Thread("Unknow");
  int* farg = (int*) malloc(2* sizeof(int));  printf("cnp %d\n", currentThread->space->numPages );

  farg[0]=f;
  farg[1]=arg;
  currentThread->space->threads++;
  newThread->Fork(&StartUserThread, (int) farg);
  return 0;
}


#include "usersynch.h"

Semaphore *
UserSemaphore (const char *debugName, int initialValue)
{
  //printf("%s\n",debugName );
  //printf("%d\n",initialValue );
  Semaphore* ret=new Semaphore(debugName,initialValue);
  //printf("%p\n", ret);
  return ret;
}



/*~UserSemaphore ()
{
  delete sema;
}*/



void
P (Semaphore* semaphore)
{
  //printf("%p\n", semaphore);
  semaphore->P();
}


void
V (Semaphore* semaphore)
{
  semaphore->V();
}

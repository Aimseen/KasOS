

#include "copyright.h"
#include "synch.h"

typedef Semaphore* SemaphoreT;

extern Semaphore* UserSemaphore (const char *debugName, int initialValue);
extern void P (Semaphore* semaphore);
extern void V (Semaphore* semaphore);

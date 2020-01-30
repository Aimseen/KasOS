#include "syscall.h"
#define THIS "a"
#define AZER "b"
const int N = 10; // Choose it large enough!

//static void* sema;
typedef struct parametre parametre;
struct parametre
{
    void* print;
    int sema;
};

void puts(char *s){
  char *p;
  for (p = s; *p != '\0'; p++){
    PutChar(*p);
  }
}
void f(parametre *s){
  int i;
  P(s->sema);
  for (i = 0; i < N; i++){
    puts((char *)s->print);
  }
  V(s->sema);
  UserThreadExit();
}

int main(){
  int sema=UserSemaphore ("eee", 1);
  parametre p1={(void *)THIS,sema};
  int a=UserThreadCreate((void (*)(void *))f,(void *)&p1);
  parametre p2={(void *)AZER,sema};
  int b=UserThreadCreate((void (*)(void *))f, (void *)&p2);
  UserThreadJoin(a);
  UserThreadJoin(b);
  return 0;
}

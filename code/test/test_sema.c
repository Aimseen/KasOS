#include "syscall.h"
#define THIS "a"
#define AZER "b"
const int N = 10; // Choose it large enough!

static void* sema;
/*typedef struct parametre parametre;
struct parametre
{
    void* print;
    void* sema;
};*/

void puts(char *s){
  char *p;
  for (p = s; *p != '\0'; p++){
    PutChar(*p);
  }
}
void f(void *s){
  int i;
  P(sema);
  for (i = 0; i < N; i++){
    puts((char *)s);
  }
  V(sema);
  UserThreadExit();
}

int main(){
  sema=UserSemaphore ("eee", 1);
  //parametre p1={(void *)THIS,s};
  int a=UserThreadCreate(f, (void *)THIS);
  //parametre p2={(void *)AZER,s};
  int b=UserThreadCreate(f, (void *)AZER);
  UserThreadJoin(a);
  UserThreadJoin(b);
  return 0;
}

#include "syscall.h"
#define THIS "c"
#define THAT "d"
const int N = 10; // Choose it large enough!
void puts(char *s){
  char *p;
  for (p = s; *p != '\0'; p++){
    PutChar(*p);
  }
}
void f(void *s){
  int i;
  for (i = 0; i < N; i++){
    puts((char *)s);
  }
  UserThreadExit();
}
void fu(void *s){
  int i;
  for (i = 0; i < N; i++){
    puts((char *)s);
  }

}

int main(){
  puts("debut2");
  int j=UserThreadCreate(f, (void *) THIS);
  fu((void*) THAT);
  UserThreadJoin(j);
  return 0;
}

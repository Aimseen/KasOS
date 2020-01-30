#include "syscall.h"
#define THIS "a"
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

int main(){
  int a=UserThreadCreate(f, (void *) THIS);
  int b=UserThreadCreate(f, (void *) THIS);
  int c=UserThreadCreate(f, (void *) THIS);
  int d=UserThreadCreate(f, (void *) THIS);
  int e=UserThreadCreate(f, (void *) THIS);
  int m=UserThreadCreate(f, (void *) THIS);
  int g=UserThreadCreate(f, (void *) THIS);
  int h=UserThreadCreate(f, (void *) THIS);
  int i=UserThreadCreate(f, (void *) THIS);
  int j=UserThreadCreate(f, (void *) THIS);
  int k=UserThreadCreate(f, (void *) THIS);
  int l=UserThreadCreate(f, (void *) THIS);
  UserThreadJoin(a);
  UserThreadJoin(b);
  UserThreadJoin(c);
  UserThreadJoin(d);
  UserThreadJoin(e);
  UserThreadJoin(m);
  UserThreadJoin(g);
  UserThreadJoin(h);
  UserThreadJoin(i);
  UserThreadJoin(j);
  UserThreadJoin(k);
  UserThreadJoin(l);
  return 0;
}

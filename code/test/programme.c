#include "syscall.h"

int a = 5;

void printf(char *c, int n){
  SynchPutString(c,n);
}

void test() {
  printf("abcd",4);
  UserThreadExit();
}

int main() {

  printf("Debut test program.c", 20);
  int ret1=UserThreadCreate(test, &a);
  int ret2=UserThreadCreate(test, &a);
  UserThreadJoin(ret2);
  int ret3=UserThreadCreate(test, &a);
  int ret4=UserThreadCreate(test, &a);
  UserThreadJoin(ret1);
  UserThreadJoin(ret3);
  UserThreadJoin(ret4);


  return 0;
}

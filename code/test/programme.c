#include "syscall.h"

int a = 5;

void printf(char *c, int n){
  SynchPutString(c,n);
}

void test() {
  PutChar('v');
  printf("abcd",4);
  PutChar('z');
  PutChar('m');
  UserThreadExit();
}

int main() {

  printf("Debut test program.c", 20);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);
  UserThreadCreate(test, &a);

  return 0;
}

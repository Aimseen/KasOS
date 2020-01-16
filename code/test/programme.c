#include "syscall.h"

int a = 5;

void printf(char *c, int n){
  SynchPutString(c,n);
  PutChar('\n');
}

void test() {
  printf("abcd",4);
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

#include "syscall.h"

int a = 5;

void printf(char *c, int n){
  SynchPutString(c,n);
  PutChar('\n');
}

void test() {
  printf("test",4);
  UserThreadExit();
}

int main() {

  UserThreadCreate(test, &a);

  return 0;
}

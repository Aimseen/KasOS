#include "syscall.h"

void printf(char *c, int n){
  SynchPutString(c,n);
  PutChar('\n');
}

void test() {
  printf("test",4);
}

int main() {
  Fork(test);
  return 0;
}

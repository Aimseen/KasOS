#include "syscall.h"
char test(){
  return 'a';
}

int main(){
  char c = test();
  PutChar(c);
  return 0;
}

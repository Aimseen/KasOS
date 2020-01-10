#include "syscall.h"
void scanf(char *c, int n){
  SynchGetString(c,n);
}

void printf(char *c, int n){
  SynchPutString(c,n);
  PutChar('\n');
}

int main(){
  char tmp[4];
  for(;;){
    scanf(tmp,4);
    printf(tmp,4);
  }
  Halt();
}

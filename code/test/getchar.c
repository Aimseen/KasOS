#include "syscall.h"

int main(){
  for(;;){
    char ret=SynchGetChar();
    PutChar(ret);
  }
  Halt();
}

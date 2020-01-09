#include "syscall.h"

int main(){
  char tmp[4];
  for(;;){
    SynchGetString(tmp,4);
    SynchPutString(tmp,4);
  }
  Halt();
}

#include "syscall.h"

int sscanf(){
  int i[1];
  SynchGetInt(i);
  return i[0];
}

void snprintf(int i){
  SynchPutInt(i);
  PutChar('\n');
}

int main(){
  for(;;){
    int tmp=sscanf();
    snprintf(tmp);
  }
  Halt();
}

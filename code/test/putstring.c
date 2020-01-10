#include "syscall.h"

void printf(char *c, int n){
  SynchPutString(c,n);
  PutChar('\n');
}

int main(){
  char *s = "az\nertyuioqsdfghjklmxcvbn,;:efghjklfghjjklmfghjklaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaan";
  printf(s, 300);
  printf(s, 5);
  Halt();
}

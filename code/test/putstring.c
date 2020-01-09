#include "syscall.h"


int main(){
  char *s = "az\nertyuioqsdfghjklmxcvbn,;:efghjklfghjjklmfghjklaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaan";
  SynchPutString(s, 300);
  SynchPutString(s, 5);
  Halt();
}

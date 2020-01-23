#include "syscall.h"




int main(){
  ForkExec("../build/userpages0");
  ForkExec("../build/userpages2");
  return 0;
}

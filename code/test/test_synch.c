#include "syscall.h"

int a = 5;

/*void printf(char *c, int n){
  SynchPutString(c+'\n',n+1);
}
void printChar(const char c){
  PutChar(c);
}*/
void test1() {
  SynchPutString("abcd\n",5);
  SynchPutInt(1);
  UserThreadExit();
}
void test2() {
  SynchPutString("fghi\n",5);
  SynchPutInt(2);
  UserThreadExit();
}

int main() {

  //printf("Debut test_synch.c", 18);
  UserThreadCreate(test1, &a);
  UserThreadCreate(test2, &a);
  UserThreadCreate(test1, &a);
  UserThreadCreate(test2, &a);
  UserThreadCreate(test1, &a);
  UserThreadCreate(test2, &a);
  UserThreadCreate(test1, &a);
  UserThreadCreate(test2, &a);

  return 0;
}

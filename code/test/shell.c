#include "syscall.h"

int stringcompare(char * str, char * str2, int start,int len) {
  int i = start;
  while(str[i] != '\0' && i < len) {
    if (!(str2[i] != '\0' && str2[i] == str[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

char * secondarg(char *s) {
  int i = 0;
  while(s[i] != '\0' && s[i] != ' ') {
    i++;
  }
  return s+i;
}

int
main ()
{
  char prompt[2], buffer[127], dir[20];
  int i;

  prompt[0] = '-';
  prompt[1] = '\0';
  dir[0] = ' ';
  dir[1] = '\0';

  while (1)
  {
    SynchPutString(dir,20);
    SynchPutString(prompt, 2);

    i = 0;

    do
    {

      buffer[i] = SynchGetChar();

    }
    while (buffer[i++] != '\n');

    buffer[--i] = '\0';

    if (i > 0)
    {
      if(stringcompare(buffer,"cd",0,2)){
        char * dirname = secondarg(buffer);
        ChangeDir(dirname);
        dir = dirname;
      } else if(stringcompare(buffer, "mkdir",0,5)) {
        char * dirname = secondarg(buffer);
        AddDir(dirname);
      }else {
        ForkExec(buffer);
      }
    }
  }
}

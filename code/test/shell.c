#include "syscall.h"

char* parser(char* str, int size)
{
	char delim[] = " ";

  char* cursor = str;
  char* ptr = cursor;
    int i = 0;
    while(i<size || *cursor != *delim){
      if(*cursor == '\0') ptr = cursor;
      cursor++;
    }
    if(*cursor == *delim){
      *cursor = '\0';
      return ptr;
    }


    return 0;
}

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
      if(stringcompare(parser(buffer, 127), "cd",0,5)){
        char * dirname = parser(buffer, 127);
        SynchPutString(dirname, 127);
        ChangeDir(dirname);
        //dir = dirname;
      } else if(stringcompare(parser(buffer, 127), "mkdir",0,5)) {
        char * dirname = secondarg(parser(buffer, 127));
        AddDir(dirname);
      }else {
        ForkExec(parser(buffer, 127));
      }
    }
  }
}

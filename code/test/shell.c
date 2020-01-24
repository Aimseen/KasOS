#include "syscall.h"

int
main ()
{
  char prompt[2], buffer[127];
  int i;

  prompt[0] = '-';
  prompt[1] = '\0';

  while (1)
  {
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
      ForkExec(buffer);
    }
  }
}

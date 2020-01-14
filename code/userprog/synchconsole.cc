#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile){
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}

SynchConsole::~SynchConsole(){
  delete console;
  delete writeDone;
  delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch){
  console->PutChar(ch);
  writeDone->P();

}

char SynchConsole::SynchGetChar(){
  readAvail->P();
  return console->GetChar();
}

void SynchConsole::SynchPutString(const char s[]){
  int i=0;
  while(s[i] != '\0'){
    SynchPutChar(s[i]);
    ++i;
  }
}

void SynchConsole::SynchGetString(char *s, int n){

  for(int i=0; i<n; i++){
    char tmp = SynchGetChar();
    if(tmp ==EOF || tmp=='\n' || tmp =='\0'){
      s[i]='\0';
      break;
    }
    s[i]=tmp;
  }
}

void SynchConsole::SynchPutInt(int n){
  stringstream strs;
  strs << n;
  string temp_str = strs.str();
  char* char_type = (char*) temp_str.c_str();
  SynchPutString(char_type);
}

void SynchConsole::SynchGetInt(int *n){
  char tmp[11];
  SynchGetString(tmp,11);
  *n =atoi(tmp);
}

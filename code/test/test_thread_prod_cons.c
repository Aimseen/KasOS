#include "syscall.h"

const int N = 10; // Choose it large enough!

typedef struct parametre parametre;
struct parametre
{
    int id;
    int verrou;
    int plein;
    int vide;
};

void producteur(parametre* par){
    P(par->verrou);
    SynchPutString("Debut Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);

    P(par->vide);

    V(par->plein);

    P(par->verrou);
    SynchPutString("Fin Producteur:",30);
    SynchPutInt(par->id);
    PutChar('\n');
    V(par->verrou);
  UserThreadExit();

}


void consomateur(parametre* par){
  P(par->verrou);
  SynchPutString("Debut Consomateur:",30);
  SynchPutInt(par->id);
  PutChar('\n');
  V(par->verrou);

  P(par->plein);
  V(par->vide);

  P(par->verrou);
  SynchPutString("Fin Consomateur:",30);
  SynchPutInt(par->id);
  PutChar('\n');
  V(par->verrou);

  UserThreadExit();
}


int main(){
  //////////////////////////////////////////////////////////////////////////////
  //initialisation structure pour les threads
  //////////////////////////////////////////////////////////////////////////////
  int verrou=UserSemaphore ("verrou", 1);
  int plein=UserSemaphore ("plein", 0);
  int vide=UserSemaphore ("vide", 5);
  int tab[100];
  parametre parametres[100];
  int nbThread=0;
  //////////////////////////////////////////////////////////////////////////////
  //lance
  //////////////////////////////////////////////////////////////////////////////
  for(;nbThread<20;nbThread++){
    parametre p={nbThread,verrou,plein,vide};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))producteur,(void *)&parametres[nbThread]);
  }
  for(;nbThread<40;nbThread++){
    parametre p={nbThread,verrou,plein,vide};
    parametres[nbThread]=p;
    tab[nbThread]=UserThreadCreate((void (*)(void *))consomateur,(void *)&parametres[nbThread]);
  }
  //SynchPutString("Fin Lancer!!!!!!!!",30);
  //////////////////////////////////////////////////////////////////////////////
  //Attente des thread lancer durant le test
  //////////////////////////////////////////////////////////////////////////////
  /*PutChar('a');
  UserThreadJoin(tab[10]);
  PutChar('b');*/


  int i;
  for(i=0;i<nbThread;i++){
    SynchPutString("join::",30);
    SynchPutInt(i);
    PutChar('\n');
    UserThreadJoin(tab[i]);
  }

  return 0;
}
